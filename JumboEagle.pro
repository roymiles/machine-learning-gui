#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += opengl # Maybe dont need?
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    Core/Graph/block.cpp \
    Core/Graph/customblock.cpp \
    Core/Graph/edge.cpp \
    Core/Graph/graphwidget.cpp \
    Core/Graph/inputport.cpp \
    Core/Graph/mycustomblock.cpp \
    Core/Graph/outputport.cpp \
    Core/Graph/port.cpp \
    Core/IO/filemanager.cpp \
    Core/UI/addblockdialog.cpp \
    Core/linearregression.cpp \
    Core/main.cpp \
    Core/mainwindow.cpp \
    Core/utilities.cpp

HEADERS += \
    Core/Graph/block.h \
    Core/Graph/customblock.h \
    Core/Graph/edge.h \
    Core/Graph/graphwidget.h \
    Core/Graph/inputport.h \
    Core/Graph/mycustomblock.h \
    Core/Graph/outputport.h \
    Core/Graph/port.h \
    Core/IO/filemanager.h \
    Core/UI/addblockdialog.h \
    Core/debug.h \
    Core/linearregression.h \
    Core/mainwindow.h \
    Core/plot.h \
    Core/utilities.h \
    Dependencies/qcustomplot-source/qcustomplot.h

FORMS += \
    Core/UI/addblockdialog.ui \
    Core/mainwindow.ui

DISTFILES += \
    bg.svg

SUBDIRS += \
    JumboEagle.pro

#LIBS += opengl32.lib

INCLUDEPATH += Dependencies\
#INCLUDEPATH += Dependencies\qcustomplot-source
#INCLUDEPATH += Dependencies\opencv-2.4.13.6\opencv\build\include
#INCLUDEPATH += Dependencies\darkstyle\framelesswindow
#INCLUDEPATH += Dependencies\darkstyle

#RESOURCES += \
#    Dependencies/darkstyle/framelesswindow.qrc \
#    Dependencies/darkstyle/darkstyle.qrc


#LIBS += -L$$PWD/Dependencies/opencv-2.4.13.6/opencv/build/x86/vc14/lib -lopencv_core2413d
#INCLUDEPATH += $$PWD/Dependencies/opencv-2.4.13.6/opencv/build/include
