#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T15:42:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PianoPractice
TEMPLATE = app

INCLUDEPATH +=

SOURCES += main.cpp\
        mw.cpp\
    rtmidiwrapper.cpp \
    miditrack.cpp \
    appcontext.cpp \
    midisong.cpp \
    midievent.cpp
        

HEADERS  += mw.h\
    rtmidiwrapper.h \
    miditrack.h \
    appcontext.h \
    midisong.h \
    midievent.h

FORMS    += mw.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../rtmidi-2.1.0/release/ -lrtmidi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../rtmidi-2.1.0/debug/ -lrtmidi
else:unix: LIBS += -L$$PWD/../rtmidi-2.1.0/ -lrtmidi

INCLUDEPATH += $$PWD/../rtmidi-2.1.0
DEPENDPATH += $$PWD/../rtmidi-2.1.0
