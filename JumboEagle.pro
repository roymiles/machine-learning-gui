#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += opengl # Maybe dont need?
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JumboEagle
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
        mainwindow.cpp \
    graphwidget.cpp \
    filemanager.cpp \
    addblockdialog.cpp \
    inputport.cpp \
    port.cpp \
    customblock.cpp \
    block.cpp \
    mycustomblock.cpp \
    outputport.cpp \
    edge.cpp \
    linearregression.cpp \
    utilities.cpp

HEADERS += \
        mainwindow.h \
    debug.h \
    mainwindow.h \
    graphwidget.h \
    filemanager.h \
    addblockdialog.h \
    inputport.h \
    port.h \
    customblock.h \
    block.h \
    mycustomblock.h \
    outputport.h \
    utilities.h \
    edge.h \
    matrix.h \
    linearregression.h

FORMS += \
        mainwindow.ui \
    addblockdialog.ui

DISTFILES += \
    bg.svg

SUBDIRS += \
    JumboEagle.pro

#LIBS += opengl32.lib

INCLUDEPATH += Dependencies\
#INCLUDEPATH += Dependencies\opencv-2.4.13.6\opencv\build\include
#INCLUDEPATH += Dependencies\darkstyle\framelesswindow
#INCLUDEPATH += Dependencies\darkstyle

#RESOURCES += \
#    Dependencies/darkstyle/framelesswindow.qrc \
#    Dependencies/darkstyle/darkstyle.qrc


#LIBS += -L$$PWD/Dependencies/opencv-2.4.13.6/opencv/build/x86/vc14/lib -lopencv_core2413d
#INCLUDEPATH += $$PWD/Dependencies/opencv-2.4.13.6/opencv/build/include
