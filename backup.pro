QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = bin
UI_DIR = .

app {
        TARGET = backup
        OBJECTS_DIR = build/backup
        MOC_DIR = build/backup

	SOURCES += src/main.cpp \
    		src/backup.cpp

	HEADERS += \
   		 src/backup.h
}

backuptest {
        QT += testlib
        TARGET = backuptest
        OBJECTS_DIR = build/backuptest
        MOC_DIR = build/backuptest

	SOURCES += \
                tests/backuptest/backuptest.cpp \
    		src/backup.cpp \

	HEADERS += \
    		src/backup.h
}
