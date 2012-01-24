/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Mobility Components.
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

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickItem>
#include "qmlapplicationviewer.h"
#include "trace.h"

#ifdef PERFORMANCEMONITOR_SUPPORT
#include "performancemonitordeclarative.h"
#endif

static const QString DefaultFileName1 = "";
static const QString DefaultFileName2 = "";

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef PERFORMANCEMONITOR_SUPPORT
    PerformanceMonitor::qmlRegisterTypes();
#endif

    QString source1, source2;
    qreal volume = 0.5;
    QStringList args = app.arguments();
    PerformanceMonitor::State performanceMonitorState;
    bool sourceIsUrl = false;
    for (int i=1; i<args.count(); ++i) {
        const QString &arg = args.at(i);
        if (arg.startsWith('-')) {
            if ("-volume" == arg) {
                if (i+1 < args.count())
                    volume = 0.01 * args.at(++i).toInt();
                else
                    qtTrace() << "Option \"-volume\" takes a value";
            }
#ifdef PERFORMANCEMONITOR_SUPPORT
            else if (PerformanceMonitor::parseArgument(arg, performanceMonitorState)) {
                // Do nothing
            }
#endif
            else if ("-url" == arg) {
                sourceIsUrl = true;
            } else {
                qtTrace() << "Option" << arg << "ignored";
            }
        } else {
            if (source1.isEmpty())
                source1 = arg;
            else if (source2.isEmpty())
                source2 = arg;
            else
                qtTrace() << "Argument" << arg << "ignored";
        }
    }

    QUrl url1, url2;
    if (sourceIsUrl) {
        url1 = source1;
        url2 = source2;
    } else {
        if (!source1.isEmpty())
            url1 = QUrl::fromLocalFile(source1);
        if (!source2.isEmpty())
            url2 = QUrl::fromLocalFile(source2);
    }

    QmlApplicationViewer viewer;

    viewer.requestWindowOrientation(Qt::LandscapeOrientation);
    viewer.setMainQmlFile(QLatin1String("qml/qmlvideo/main.qml"));
    QQuickItem *rootObject = viewer.rootObject();
    rootObject->setProperty("source1", url1);
    rootObject->setProperty("source2", url2);
    rootObject->setProperty("volume", volume);

#ifdef PERFORMANCEMONITOR_SUPPORT
    if (performanceMonitorState.valid) {
        rootObject->setProperty("perfMonitorsLogging", performanceMonitorState.logging);
        rootObject->setProperty("perfMonitorsVisible", performanceMonitorState.visible);
    }
    QObject::connect(&viewer, SIGNAL(afterRendering()),
                     rootObject, SLOT(qmlFramePainted()));
#endif

    QMetaObject::invokeMethod(rootObject, "init");

    viewer.showExpanded();

    return app.exec();
}

