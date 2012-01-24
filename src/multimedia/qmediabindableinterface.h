/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Toolkit.
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

#ifndef QMEDIABINDABLEINTERFACE_H
#define QMEDIABINDABLEINTERFACE_H

#include <qmediaobject.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Multimedia)


class QMediaObject;

class Q_MULTIMEDIA_EXPORT QMediaBindableInterface
{
public:
    virtual ~QMediaBindableInterface();

    virtual QMediaObject *mediaObject() const = 0;

protected:
    friend class QMediaObject;
    virtual bool setMediaObject(QMediaObject *object) = 0;
};

#define QMediaBindableInterface_iid \
    "com.nokia.Qt.QMediaBindableInterface/1.0"
Q_DECLARE_INTERFACE(QMediaBindableInterface, QMediaBindableInterface_iid)

QT_END_NAMESPACE

QT_END_HEADER


#endif  // QMEDIABINDABLEINTERFACE_H
