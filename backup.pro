QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = bin
UI_DIR = .

SOURCES += \
        src/backup.cpp \
        src/backupcli.cpp

HEADERS += \
         src/backup.h \
         src/backupcli.h

app {
        TARGET = backup
        OBJECTS_DIR = build
        MOC_DIR = build

        SOURCES += src/main.cpp
}

backuptest {
        QT += testlib
        TARGET = backuptest
        OBJECTS_DIR = build
        MOC_DIR = build

        SOURCES += tests/backuptest/backuptest.cpp
}

backupclitest {
        QT += testlib
        TARGET = backupclitest
        OBJECTS_DIR = build
        MOC_DIR = build

        SOURCES += tests/backupclitest/backupclitest.cpp
}
