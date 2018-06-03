#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
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
    block.cpp \
    graphwidget.cpp \
    link.cpp \
    filemanager.cpp \
    addblockdialog.cpp

HEADERS += \
        mainwindow.h \
    debug.h \
    block.h \
    mainwindow.h \
    graphwidget.h \
    link.h \
    filemanager.h \
    addblockdialog.h

FORMS += \
        mainwindow.ui \
    addblockdialog.ui

DISTFILES += \
    bg.svg

SUBDIRS += \
    JumboEagle.pro

LIBS += opengl32.lib

INCLUDEPATH += Dependencies\opencv-2.4.13.6\opencv\build\include
INCLUDEPATH += Dependencies\darkstyle\framelesswindow
INCLUDEPATH += Dependencies\darkstyle

LIBS += -L"C:/Users/Roy/Documents/JumboEagle/Dependencies/opencv-2.4.13.6/opencv/build/x86/vc14/lib"
#        LIBS += "-lopencv_calib3d2413"
#        LIBS += "-lopencv_contrib2413"
        LIBS += -lopencv_core2413
#        LIBS += "-lopencv_features2d2413"
#        LIBS += "-lopencv_flann2413"
#        LIBS += "-lopencv_gpu2413"
#        LIBS += "-lopencv_highgui2413"
#        LIBS += "-lopencv_imgproc2413"
#        LIBS += "-lopencv_legacy2413"
#        LIBS += "-lopencv_ml2413"
#        LIBS += "-lopencv_nonfree2413"
#        LIBS += "-lopencv_objdetect2413"
#        LIBS += "-lopencv_ocl2413"
#        LIBS += "-lopencv_photo2413"
#        LIBS += "-lopencv_stitching2413"
#        LIBS += "-lopencv_superres2413"
#        LIBS += "-lopencv_ts2413"
#        LIBS += "-lopencv_video2413"
#        LIBS += "-lopencv_videostab2413"

RESOURCES += \
    Dependencies/darkstyle/framelesswindow.qrc \
    Dependencies/darkstyle/darkstyle.qrc
