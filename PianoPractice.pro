#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T15:42:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PianoPractice
TEMPLATE = app

SOURCES += main.cpp\
        mw.cpp\
        

HEADERS  += mw.h\

FORMS    += mw.ui

unix|win32: LIBS += -lrtmidi
