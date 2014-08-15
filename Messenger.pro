#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T22:15:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    loginform.cpp \
    registerform.cpp \
    mtabwidget.cpp \
    networkhandle.cpp \
    storagehandle.cpp \
    model.cpp \
    splashscreen.cpp \
    buttonaddfriend.cpp \
    dialogzadodavanjeprijatelja.cpp \
    pomerac.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    registerform.h \
    mtabwidget.h \
    networkhandle.h \
    storagehandle.h \
    model.h \
    Poruka.h \
    splashscreen.h \
    buttonaddfriend.h \
    dialogzadodavanjeprijatelja.h \
    pomerac.h

FORMS    += mainwindow.ui \
    loginform.ui \
    registerform.ui \
    dialogzadodavanjeprijatelja.ui

RESOURCES = slike.qrc
