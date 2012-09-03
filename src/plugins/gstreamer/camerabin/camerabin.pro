TARGET = gstcamerabin
PLUGIN_TYPE = mediaservice

QT += multimedia-private

load(qt_plugin)
DESTDIR = $$QT.multimedia.plugins/$${PLUGIN_TYPE}

include(../common.pri)

INCLUDEPATH += $$PWD \
    $${SOURCE_DIR}/src/multimedia

INCLUDEPATH += camerabin


HEADERS += \
    $$PWD/camerabinserviceplugin.h \
    $$PWD/camerabinservice.h \
    $$PWD/camerabinsession.h \
    $$PWD/camerabincontrol.h \
    $$PWD/camerabinaudioencoder.h \
    $$PWD/camerabinimageencoder.h \
    $$PWD/camerabinrecorder.h \
    $$PWD/camerabincontainer.h \
    $$PWD/camerabinimagecapture.h \
    $$PWD/camerabinimageprocessing.h \
    $$PWD/camerabinmetadata.h \
    $$PWD/camerabinvideoencoder.h \
    $$PWD/camerabinresourcepolicy.h \
    $$PWD/camerabincapturedestination.h \
    $$PWD/camerabincapturebufferformat.h

SOURCES += \
    $$PWD/camerabinserviceplugin.cpp \
    $$PWD/camerabinservice.cpp \
    $$PWD/camerabinsession.cpp \
    $$PWD/camerabincontrol.cpp \
    $$PWD/camerabinaudioencoder.cpp \
    $$PWD/camerabincontainer.cpp \
    $$PWD/camerabinimagecapture.cpp \
    $$PWD/camerabinimageencoder.cpp \
    $$PWD/camerabinimageprocessing.cpp \
    $$PWD/camerabinmetadata.cpp \
    $$PWD/camerabinrecorder.cpp \
    $$PWD/camerabinvideoencoder.cpp \
    $$PWD/camerabinresourcepolicy.cpp \
    $$PWD/camerabincapturedestination.cpp \
    $$PWD/camerabincapturebufferformat.cpp

maemo6 {
    HEADERS += \
        $$PWD/camerabuttonlistener_meego.h

    SOURCES += \
        $$PWD/camerabuttonlistener_meego.cpp

    CONFIG += have_gst_photography
}

have_gst_photography {
    DEFINES += HAVE_GST_PHOTOGRAPHY

    HEADERS += \
        $$PWD/camerabinfocus.h \
        $$PWD/camerabinexposure.h \
        $$PWD/camerabinflash.h \
        $$PWD/camerabinlocks.h

    SOURCES += \
        $$PWD/camerabinexposure.cpp \
        $$PWD/camerabinflash.cpp \
        $$PWD/camerabinfocus.cpp \
        $$PWD/camerabinlocks.cpp

    LIBS += -lgstphotography-0.10
    DEFINES += GST_USE_UNSTABLE_API #prevents warnings because of unstable photography API
}



target.path += $$[QT_INSTALL_PLUGINS]/$${PLUGIN_TYPE}
INSTALLS += target

OTHER_FILES += \
    camerabin.json

