#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T14:17:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Informer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    traywidget.cpp \
    screen.cpp \
    messageframe.cpp \
    uistate.cpp

HEADERS  += widget.h \
    traywidget.h \
    screen.h \
    messageframe.h \
    uistate.h

FORMS    += widget.ui \
    messageframe.ui

RESOURCES += \
    images.qrc
