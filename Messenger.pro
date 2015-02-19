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
    networkhandle.cpp \
    storagehandle.cpp \
    model.cpp \
    splashscreen.cpp \
    buttonaddfriend.cpp \
    dialogzadodavanjeprijatelja.cpp \
    painterholder.cpp \
    widget.cpp \
    listwidgetzaprijatelje.cpp \
    statuswidget.cpp \
    listviewzaporuke.cpp \
    dugmad.cpp \
    painterHolderTester.cpp \
    podesavanja.cpp \
    debugprozor.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    registerform.h \
    networkhandle.h \
    storagehandle.h \
    model.h \
    Poruka.h \
    splashscreen.h \
    buttonaddfriend.h \
    dialogzadodavanjeprijatelja.h \
    painterholder.h \
    widget.h \
    listwidgetzaprijatelje.h \
    statuswidget.h \
    listviewzaporuke.h \
    dugmad.h \
    podesavanja.h \
    debugprozor.h

FORMS    += mainwindow.ui \
    loginform.ui \
    registerform.ui \
    dialogzadodavanjeprijatelja.ui \
    widget.ui \
    podesavanja.ui \
    debugprozor.ui

RESOURCES = slike.qrc
