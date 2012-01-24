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

import QtQuick 2.0

Rectangle {
    id: root
    width: 640
    height: 360
    color: "grey"
    property string fileName
    property alias volume: content.volume
    property bool perfMonitorsLogging: false
    property bool perfMonitorsVisible: false

    QtObject {
        id: d
        property string openFileType
    }

    // Create ScreenSaver element via Loader, so this app will still run if the
    // SystemInfo module is not available
    Loader {
        source: "DisableScreenSaver.qml"
    }

    Loader {
        id: performanceLoader
        function init() {
            console.log("[qmlvideofx] performanceLoader.init logging " + root.perfMonitorsLogging + " visible " + root.perfMonitorsVisible)
            var enabled = root.perfMonitorsLogging || root.perfMonitorsVisible
            source = enabled ? "../performancemonitor/PerformanceItem.qml" : ""
        }
        onLoaded: {
            item.parent = root
            item.anchors.top = root.top
            item.anchors.topMargin = 100
            item.anchors.left = root.left
            item.anchors.right = root.right
            item.anchors.bottom = root.verticalCenter
            item.logging = root.perfMonitorsLogging
            item.displayed = root.perfMonitorsVisible
            item.init()
        }
    }

    Rectangle {
        id: inner
        anchors.fill: parent
        color: "grey"

        Content {
            id: content
            anchors.fill: parent
            gripSize: 40
            onVideoFramePainted: performanceLoader.item.videoFramePainted()
        }

        ParameterPanel {
            id: parameterPanel
            anchors {
                left: parent.left;
                right: parent.right;
                margins: 10
            }
            y: parent.height
            gripSize: 40

            states: [
                State {
                    name: "shown"
                    PropertyChanges {
                        target: parameterPanel
                        y: parent.height - (parameterPanel.height + 10)
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation {
                        properties: "y"
                        easing.type: Easing.OutQuart
                        duration: 500
                    }
                }
            ]

            enabled: false
            state: enabled ? "shown" : "baseState"
        }

        EffectSelectionPanel {
            id: effectSelectionPanel
            anchors {
                top: parent.top;
                bottom: parameterPanel.top;
                margins: 10
            }
            x: parent.width
            width: parent.width - 40
            opacity: 0.75
            radius: 20
            itemHeight: 50

            states: [
                State {
                    name: "shown"
                    PropertyChanges {
                        target: effectSelectionPanel
                        x: 20
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation {
                        properties: "x"
                        easing.type: Easing.OutQuart
                        duration: 500
                    }
                }
            ]

            onEffectSourceChanged: {
                content.effectSource = effectSource
                if (content.effect.parameters.count) {
                    parameterPanel.model = content.effect.parameters
                    parameterPanel.enabled = true
                } else {
                    parameterPanel.enabled = false
                }
            }

            onClicked: state = "baseState"
        }

        Rectangle {
            id: fileOpenContainer
            anchors {
                top: parent.top
                bottom: parameterPanel.top
                margins: 10
            }
            x: -width
            width: parent.width - 40
            color: "transparent"

            Column {
                anchors.fill: parent

                FileOpen {
                    id: fileOpen
                    color: "transparent"
                    width: parent.width
                    height: 200
                    opacity: 0.75
                    radius: 20
                    buttonHeight: 40
                }

                MouseArea {
                    width: parent.width
                    height: 250
                    onClicked: fileOpenContainer.state = "baseState"
                }
            }

            states: [
                State {
                    name: "shown"
                    PropertyChanges {
                        target: fileOpenContainer
                        x: 20
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation {
                        properties: "x"
                        easing.type: Easing.OutQuart
                        duration: 500
                    }
                }
            ]
        }

        Rectangle {
            id: splashScreen
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            width: 300
            height: 200
            radius: 0.1 * height
            color: "white"
            opacity: 0.9
            border { color: "black"; width: 2 }

            Text {
                anchors {
                    fill: parent
                    margins: 5
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 24
                text: "Tap on left side to switch between sources.\n\nTap on right side to switch between effects."
                wrapMode: Text.WordWrap
            }

            MouseArea {
                anchors.fill: parent
                onClicked: parent.state = "hidden"
            }

            states: [
                State {
                    name: "hidden"
                    PropertyChanges {
                        target: splashScreen
                        opacity: 0.0
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation {
                        properties: "opacity"
                        easing.type: Easing.OutQuart
                        duration: 500
                    }
                }
            ]
        }

        HintedMouseArea {
            id: fileOpenMouseArea
            anchors {
                left: parent.left;
                top: parent.top;
                bottom: parameterPanel.top;
                topMargin: 75
            }
            width: 100
            onClicked: {
                fileOpenMouseArea.hintEnabled = false
                effectSelectionPanelMouseArea.hintEnabled = false
                splashScreen.state = "hidden"
                fileOpenContainer.state = "shown"
            }
            enabled: (fileOpenContainer.state != "shown" && effectSelectionPanel.state != "shown")
        }

        HintedMouseArea {
            id: effectSelectionPanelMouseArea
            anchors {
                right: parent.right;
                top: parent.top;
                bottom: parameterPanel.top;
                topMargin: 75
            }
            width: 100
            onClicked: {
                fileOpenMouseArea.hintEnabled = false
                effectSelectionPanelMouseArea.hintEnabled = false
                splashScreen.state = "hidden"
                effectSelectionPanel.state = "shown"
            }
            enabled: (fileOpenContainer.state != "shown" && effectSelectionPanel.state != "shown")
        }

        Image {
            source: "qrc:/images/close.png"

            anchors {
                top: parent.top
                right: parent.right
                margins: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
        }
    }

    Component.onCompleted: {
        fileOpen.openImage.connect(openImage)
        fileOpen.openVideo.connect(openVideo)
        fileOpen.openCamera.connect(openCamera)
        fileOpen.close.connect(close)
    }

    Loader {
        id: fileBrowserLoader
    }

    // Called from main() once root properties have been set
    function init() {
        console.log("[qmlvideofx] main.init")
        content.init()
        performanceLoader.init()
        if (fileName != "") {
            fileOpenMouseArea.hintEnabled = false
            effectSelectionPanelMouseArea.hintEnabled = false
            splashScreen.state = "hidden"
            d.openFileType = "video"
            openFile(fileName)
        }
    }

    function qmlFramePainted() {
        if (performanceLoader.item)
            performanceLoader.item.qmlFramePainted()
    }

    function openImage() {
        fileOpenContainer.state = "baseState"
        d.openFileType = "image"
        showFileBrowser("../../images")
    }

    function openVideo() {
        fileOpenContainer.state = "baseState"
        d.openFileType = "video"
        showFileBrowser("../../videos")
    }

    function openCamera() {
        fileOpenContainer.state = "baseState"
        content.openCamera()
    }

    function close() {
        fileOpenContainer.state = "baseState"
        content.openImage("qrc:/images/qt-logo.png")
    }

    function showFileBrowser(path) {
        content.stop()
        fileBrowserLoader.source = "FileBrowser.qml"
        fileBrowserLoader.item.parent = root
        fileBrowserLoader.item.anchors.fill = root
        fileBrowserLoader.item.openFile.connect(root.openFile)
        fileBrowserLoader.item.folder = path
        inner.visible = false
    }

    function openFile(path) {
        fileBrowserLoader.source = ""
        if (path != "") {
            if (d.openFileType == "image")
                content.openImage(path)
            else if (d.openFileType == "video")
                content.openVideo(path)
        }
        inner.visible = true
    }
}
