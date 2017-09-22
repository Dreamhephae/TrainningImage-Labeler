#-------------------------------------------------
#
# Project created by QtCreator 2017-09-12T11:49:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Labeler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintablelabel.cpp

HEADERS  += mainwindow.h \
    paintablelabel.h \
    global.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

RC_FILE = exe_icon.rc
