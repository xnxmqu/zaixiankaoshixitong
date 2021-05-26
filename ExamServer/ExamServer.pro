#-------------------------------------------------
#
# Project created by QtCreator 2021-04-19T19:20:34
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExamServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        serverlogin.cpp \
    management.cpp \
    managestudent.cpp \
    manageteacher.cpp \
    threeques.cpp \
    teacherwidget.cpp \
    widget1.cpp \
    widget2.cpp \
    widget3.cpp \
    displaypaper.cpp \
    additem1.cpp \
    additem2.cpp \
    additem3.cpp


HEADERS += \
        serverlogin.h \
    management.h \
    managestudent.h \
    manageteacher.h \
    threeques.h \
    teacherwidget.h \
    widget1.h \
    widget2.h \
    widget3.h \
    displaypaper.h \
    additem1.h \
    additem2.h \
    additem3.h

FORMS += \
        serverlogin.ui \
    management.ui \
    managestudent.ui \
    manageteacher.ui \
    teacherwidget.ui \
    widget1.ui \
    widget2.ui \
    widget3.ui \
    displaypaper.ui \
    additem1.ui \
    additem2.ui \
    additem3.ui

CONFIG +=C++11
