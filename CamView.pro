#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T22:54:06
#
#-------------------------------------------------

QT       += core gui network multimedia

TARGET = CamView
TEMPLATE = app

VERSION = 1.1.0


SOURCES += main.cpp\
        mainwindow.cpp \
    mjpegsource.cpp \
    motiondetector.cpp \
    mjpegdumper.cpp \
    camerawidget.cpp \
    config.cpp \
    playerdialog.cpp \
    playerwidget.cpp \
    apptoolbar.cpp \
    actionmark.cpp \
    settingsdialog.cpp \
    converter.cpp \
    alawdecoder.cpp \
    audiosource.cpp \
    camerainfodialog.cpp \
    periodicrecycler.cpp \
    cameraitemsmanager.cpp \
    camerarepairer.cpp \
    mjpeghelpers.cpp

HEADERS  += mainwindow.h \
    mjpegsource.h \
    motiondetector.h \
    mjpegdumper.h \
    camerawidget.h \
    config.h \
    data.h \
    playerdialog.h \
    playerwidget.h \
    apptoolbar.h \
    actionmark.h \
    settingsdialog.h \
    converter.h \
    alawdecoder.h \
    audiosource.h \
    camerainfodialog.h \
    periodicrecycler.h \
    cameraitemsmanager.h \
    camerarepairer.h \
    mjpeghelpers.h

FORMS    += \
    playerdialog.ui \
    settingsdialog.ui \
    camerainfodialog.ui

RESOURCES += \
    resources.qrc
