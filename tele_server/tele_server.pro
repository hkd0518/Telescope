#-------------------------------------------------
#
# Project created by QtCreator 2011-02-28T14:31:12
#
#-------------------------------------------------

QT       += core gui network

TARGET = tele_server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showpic.cpp \
    transfer.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    showpic.h \
    transfer.h \
    server.h \
    ui_server.h \
    ui_mainwindow.h

FORMS    += mainwindow.ui \
    server.ui

RESOURCES += \
    tele_server.qrc
