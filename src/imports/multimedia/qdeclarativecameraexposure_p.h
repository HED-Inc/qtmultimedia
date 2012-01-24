/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDECLARATIVECAMERAEXPOSURE_H
#define QDECLARATIVECAMERAEXPOSURE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qdeclarativecamera_p.h"
#include <qcamera.h>
#include <qcameraexposure.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QDeclarativeCamera;

class QDeclarativeCameraExposure : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal exposureCompensation READ exposureCompensation WRITE setExposureCompensation NOTIFY exposureCompensationChanged)

    Q_PROPERTY(int iso READ isoSensitivity NOTIFY isoSensitivityChanged)
    Q_PROPERTY(qreal shutterSpeed READ shutterSpeed NOTIFY shutterSpeedChanged)
    Q_PROPERTY(qreal aperture READ aperture NOTIFY apertureChanged)

    Q_PROPERTY(qreal manualShutterSpeed READ manualShutterSpeed WRITE setManualShutterSpeed NOTIFY manualShutterSpeedChanged)
    Q_PROPERTY(qreal manualAperture READ manualAperture WRITE setManualAperture NOTIFY manualApertureChanged)
    Q_PROPERTY(qreal manualIso READ manualIsoSensitivity WRITE setManualIsoSensitivity NOTIFY manualIsoSensitivityChanged)

    Q_PROPERTY(QDeclarativeCamera::ExposureMode exposureMode READ exposureMode WRITE setExposureMode NOTIFY exposureModeChanged)

    Q_PROPERTY(QPointF spotMeteringPoint READ spotMeteringPoint WRITE setSpotMeteringPoint NOTIFY spotMeteringPointChanged)
    Q_PROPERTY(QDeclarativeCamera::MeteringMode meteringMode READ meteringMode WRITE setMeteringMode NOTIFY meteringModeChanged)

public:
    ~QDeclarativeCameraExposure();

    QDeclarativeCamera::ExposureMode exposureMode() const;
    qreal exposureCompensation() const;

    int isoSensitivity() const;
    qreal shutterSpeed() const;
    qreal aperture() const;

    int manualIsoSensitivity() const;
    qreal manualShutterSpeed() const;
    qreal manualAperture() const;

    QPointF spotMeteringPoint() const;
    void setSpotMeteringPoint(const QPointF &point);

    QDeclarativeCamera::MeteringMode meteringMode() const;
    void setMeteringMode(QDeclarativeCamera::MeteringMode mode);

public Q_SLOTS:
    void setExposureMode(QDeclarativeCamera::ExposureMode);
    void setExposureCompensation(qreal ev);

    void setManualAperture(qreal);
    void setManualShutterSpeed(qreal);
    void setManualIsoSensitivity(int iso);

    void setAutoAperture();
    void setAutoShutterSpeed();
    void setAutoIsoSensitivity();

Q_SIGNALS:
    void isoSensitivityChanged(int);
    void apertureChanged(qreal);
    void shutterSpeedChanged(qreal);

    void manualIsoSensitivityChanged(int);
    void manualApertureChanged(qreal);
    void manualShutterSpeedChanged(qreal);

    void exposureCompensationChanged(qreal);
    void exposureModeChanged(QDeclarativeCamera::ExposureMode);

    void meteringModeChanged(QDeclarativeCamera::MeteringMode);
    void spotMeteringPointChanged(QPointF);

private:
    friend class QDeclarativeCamera;
    QDeclarativeCameraExposure(QCamera *camera, QObject *parent = 0);

    QCameraExposure *m_exposure;
    int m_manualIso;
    qreal m_manualAperture;
    qreal m_manualShutterSpeed;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QDeclarativeCameraExposure))

QT_END_HEADER

#endif
