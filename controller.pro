#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T11:35:58
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): cache

QT       += core gui network dbus

DBUS_ADAPTORS += InfoFrame.xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DaliBoxGUI
TEMPLATE = app

CONFIG += release

target.path = /usr/bin
INSTALLS += target

INCLUDEPATH += GeneratedFiles

MOC_DIR = GeneratedFiles
OBJECTS_DIR = Objects
UI_DIR = GeneratedFiles
RCC_DIR = GeneratedFiles

SOURCES += main.cpp\
        mainwindow.cpp \
    qgpiohandler.cpp \
    InfoFrame.cpp \
    InfoFrameDBusAdaptor.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qgpiohandler.h \
    InfoFrame.h \
    InfoFrameDBusAdaptor.h \
    qcustomplot.h

FORMS    += \
    mainwindow.ui \
    InfoFrame.ui

RESOURCES += \
    controller.qrc

OTHER_FILES += \
    InfoFrame.xml
