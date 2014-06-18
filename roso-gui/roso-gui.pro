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
    robot.cpp \
    obstacle.cpp \
    model.cpp \
    view.cpp


HEADERS  += \
    robot.h \
    obstacle.h \
    model.h \
    view.h

FORMS    += dialog.ui
