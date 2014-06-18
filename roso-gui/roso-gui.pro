#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T13:54:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = roso-gui
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    robot.cpp \
    obstacle.cpp \
    model.cpp


HEADERS  += dialog.h \
    robot.h \
    obstacle.h \
    model.h

FORMS    += dialog.ui
