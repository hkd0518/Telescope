#-------------------------------------------------
#
# Project created by QtCreator 2011-03-03T20:26:01
#
#-------------------------------------------------

QT       += core gui network

TARGET = tele_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showpic.cpp \
    connectdlg.cpp \
    transfer.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    showpic.h \
    connectdlg.h \
    transfer.h \
    client.h \
    ui_mainwindow.h \
    ui_connectdlg.h \
    ui_client.h

FORMS    += mainwindow.ui \
    connectdlg.ui \
    client.ui

RESOURCES += \
    tele_client.qrc
