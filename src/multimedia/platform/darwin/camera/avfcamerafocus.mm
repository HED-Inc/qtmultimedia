/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "avfcamerafocus_p.h"
#include "avfcamerautility_p.h"
#include "avfcamera_p.h"
#include "avfcameradebug_p.h"

#include <QtCore/qdebug.h>

#include <AVFoundation/AVFoundation.h>

QT_BEGIN_NAMESPACE

namespace {

bool qt_focus_mode_supported(QCamera::FocusMode mode)
{
    // Check if QCamera::FocusMode has counterpart in AVFoundation.

    // AVFoundation has 'Manual', 'Auto' and 'Continuous',
    // where 'Manual' is actually 'Locked' + writable property 'lensPosition'.
    return mode == QCamera::FocusModeAuto
           || mode == QCamera::FocusModeManual;
}

AVCaptureFocusMode avf_focus_mode(QCamera::FocusMode requestedMode)
{
    switch (requestedMode) {
        case QCamera::FocusModeHyperfocal:
        case QCamera::FocusModeInfinity:
        case QCamera::FocusModeManual:
            return AVCaptureFocusModeLocked;
        default:
            return AVCaptureFocusModeContinuousAutoFocus;
    }

}

}

AVFCameraFocus::AVFCameraFocus(AVFCamera *camera)
      : QPlatformCameraFocus(camera),
      m_camera(camera),
      m_focusMode(QCamera::FocusModeAuto),
      m_customFocusPoint(0.5f, 0.5f),
      m_actualFocusPoint(m_customFocusPoint)
{
    Q_ASSERT(m_camera);
    connect(m_camera, SIGNAL(activeChanged(bool)), SLOT(cameraActiveChanged(bool)));
}

QCamera::FocusMode AVFCameraFocus::focusMode() const
{
    return m_focusMode;
}

void AVFCameraFocus::setFocusMode(QCamera::FocusMode mode)
{
    if (m_focusMode == mode)
        return;

    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice) {
        if (qt_focus_mode_supported(mode)) {
            m_focusMode = mode;
            Q_EMIT focusModeChanged(m_focusMode);
        } else {
            qDebugCamera() << Q_FUNC_INFO
                           << "focus mode not supported";
        }
        return;
    }

    if (isFocusModeSupported(mode)) {
        const AVFConfigurationLock lock(captureDevice);
        if (!lock) {
            qDebugCamera() << Q_FUNC_INFO
                           << "failed to lock for configuration";
            return;
        }

        captureDevice.focusMode = avf_focus_mode(mode);
        m_focusMode = mode;
    } else {
        qDebugCamera() << Q_FUNC_INFO << "focus mode not supported";
        return;
    }

    Q_EMIT focusModeChanged(m_focusMode);
}

bool AVFCameraFocus::isFocusModeSupported(QCamera::FocusMode mode) const
{
    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice)
        return false;

#ifdef Q_OS_IOS
    AVCaptureFocusMode avMode = avf_focus_mode(mode);
    switch (mode) {
        case QCamera::FocusModeAuto:
        case QCamera::FocusModeHyperfocal:
        case QCamera::FocusModeInfinity:
        case QCamera::FocusModeManual:
            return [captureDevice isFocusModeSupported:avMode];
    case QCamera::FocusModeAutoNear:
        Q_FALLTHROUGH();
    case QCamera::FocusModeAutoFar:
        return captureDevice.autoFocusRangeRestrictionSupported
            && [captureDevice isFocusModeSupported:avMode];
    }
#else
    return mode == QCamera::FocusModeAuto; // stupid builtin webcam doesn't do any focus handling, but hey it's usually focused :)
#endif
}

QPointF AVFCameraFocus::focusPoint() const
{
    return m_customFocusPoint;
}

void AVFCameraFocus::setCustomFocusPoint(const QPointF &point)
{
    if (m_customFocusPoint == point)
        return;

    if (!QRectF(0.f, 0.f, 1.f, 1.f).contains(point)) {
        // ### release custom focus point, tell the camera to focus where it wants...
        qDebugCamera() << Q_FUNC_INFO << "invalid focus point (out of range)";
        return;
    }

    m_customFocusPoint = point;
    Q_EMIT customFocusPointChanged(m_customFocusPoint);

    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice)
        return;

    if ([captureDevice isFocusPointOfInterestSupported]) {
        const AVFConfigurationLock lock(captureDevice);
        if (!lock) {
            qDebugCamera() << Q_FUNC_INFO << "failed to lock for configuration";
            return;
        }

        m_actualFocusPoint = m_customFocusPoint;
        const CGPoint focusPOI = CGPointMake(point.x(), point.y());
        [captureDevice setFocusPointOfInterest:focusPOI];
        if (m_focusMode != QCamera::FocusModeAuto)
            [captureDevice setFocusMode:AVCaptureFocusModeAutoFocus];
    } else {
        qDebugCamera() << Q_FUNC_INFO << "focus point of interest not supported";
        return;
    }
}

bool AVFCameraFocus::isCustomFocusPointSupported() const
{
    return true;
}

void AVFCameraFocus::setFocusDistance(float d)
{
#ifdef Q_OS_IOS
    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice)
        return;

    if (captureDevice.lockingFocusWithCustomLensPositionSupported) {
        qDebugCamera() << Q_FUNC_INFO << "Setting custom focus distance not supported\n";
        return;
    }

    const bool lock = [captureDevice lockForConfiguration:nil];
    if (!lock) {
        qDebugCamera() << Q_FUNC_INFO << "Failed to lock a capture device for configuration\n";
        return;
    }

    [captureDevice setFocusModeLockedWithLensPosition:d completionHandler:nil];
#else
    Q_UNUSED(d);
#endif
}

float AVFCameraFocus::focusDistance() const
{
#ifdef Q_OS_IOS
    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice)
        return 1.;
    return captureDevice.lensPosition;
#else
    return 1.;
#endif
}

void AVFCameraFocus::cameraActiveChanged(bool active)
{
    if (!active)
        return;

    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice) {
        qDebugCamera() << Q_FUNC_INFO << "capture device is nil in 'active' state";
        return;
    }

    const AVFConfigurationLock lock(captureDevice);
    if (m_customFocusPoint != m_actualFocusPoint) {
        if (![captureDevice isFocusPointOfInterestSupported]) {
            qDebugCamera() << Q_FUNC_INFO
                           << "focus point of interest not supported";
            return;
        }

        if (!lock) {
            qDebugCamera() << Q_FUNC_INFO << "failed to lock for configuration";
            return;
        }

        m_actualFocusPoint = m_customFocusPoint;
        const CGPoint focusPOI = CGPointMake(m_customFocusPoint.x(), m_customFocusPoint.y());
        [captureDevice setFocusPointOfInterest:focusPOI];
    }

    if (m_focusMode != QCamera::FocusModeAuto) {
        const AVCaptureFocusMode avMode = avf_focus_mode(m_focusMode);
        if (captureDevice.focusMode != avMode) {
            if (![captureDevice isFocusModeSupported:avMode]) {
                qDebugCamera() << Q_FUNC_INFO << "focus mode not supported";
                return;
            }

            if (!lock) {
                qDebugCamera() << Q_FUNC_INFO << "failed to lock for configuration";
                return;
            }

            [captureDevice setFocusMode:avMode];
        }
    }

#ifdef Q_OS_IOS
    const bool isActive = m_camera->isActive();
    if (!isActive) {
        if (m_maxZoomFactor > 1.) {
            m_maxZoomFactor = 1.;
            emit maximumZoomFactorChanged(1.);
        }
        return;
    }

    if (!captureDevice || !captureDevice.activeFormat) {
        qDebugCamera() << Q_FUNC_INFO << "camera state is active, but"
                       << "video capture device and/or active format is nil";
        return;
    }

    if (captureDevice.activeFormat.videoMaxZoomFactor > 1.) {
        if (!qFuzzyCompare(m_maxZoomFactor, captureDevice.activeFormat.videoMaxZoomFactor)) {
            m_maxZoomFactor = captureDevice.activeFormat.videoMaxZoomFactor;
            emit maximumZoomFactorChanged(m_maxZoomFactor);
        }
    } else if (!qFuzzyCompare(m_maxZoomFactor, CGFloat(1.))) {
        m_maxZoomFactor = 1.;

        emit maximumZoomFactorChanged(1.);
    }

    captureDevice.videoZoomFactor = m_zoomFactor;
#endif
}

AVFCameraFocus::ZoomRange AVFCameraFocus::zoomFactorRange() const
{
    return { 1., (float)m_maxZoomFactor };
}

void AVFCameraFocus::zoomTo(float factor, float rate)
{
    Q_UNUSED(factor);
    Q_UNUSED(rate);

#ifdef QOS_IOS
    if (qFuzzyCompare(CGFloat(factor), m_zoomFactor))
        return;

    m_requestedZoomFactor = factor;
    Q_EMIT requestedDigitalZoomChanged(digital);

    AVCaptureDevice *captureDevice = m_camera->device();
    if (!captureDevice || !captureDevice.activeFormat)
        return;

    m_zoomFactor = qBound(CGFloat(1.), factor, captureDevice.activeFormat.videoMaxZoomFactor);

    const AVFConfigurationLock lock(captureDevice);
    if (!lock) {
        qDebugCamera() << Q_FUNC_INFO << "failed to lock for configuration";
        return;
    }

    if (rate < 0)
        captureDevice.videoZoomFactor = clampedZoom;
    else
        [AVCaptureDevice rampToVideoZoomFactor:factor withRate:rate];
#endif
}

QT_END_NAMESPACE

#include "moc_avfcamerafocus_p.cpp"
