#-------------------------------------------------
#
# Project created by QtCreator 2016-08-21T15:40:45
#
#-------------------------------------------------

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = ../bin
UI_DIR = .

CONFIG(debug, debug|release) {
        TARGET = qt-backup-app
        OBJECTS_DIR = ../build/myapp/debug
        MOC_DIR = ../build/myapp/debug
}

CONFIG(release, debug|release) {
        TARGET = qt-backup-app
        OBJECTS_DIR = ../build/myapp/release
        MOC_DIR = ../build/myapp/release
}

SOURCES += main.cpp \
    backup.cpp

HEADERS += \
    backup.h
