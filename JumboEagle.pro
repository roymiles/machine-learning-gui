#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += opengl # Maybe dont need?
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++14
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
    Core/Graph/edge.cpp \
    Core/Graph/graphwidget.cpp \
    Core/Graph/inputport.cpp \
    Core/Graph/mycustomblock.cpp \
    Core/Graph/outputport.cpp \
    Core/Graph/port.cpp \
    Core/UI/addblockdialog.cpp \
    Core/linearregression.cpp \
    Core/main.cpp \
    Core/mainwindow.cpp \
    Core/utilities.cpp \
    Dependencies/qcustomplot-source/qcustomplot.cpp \
    Core/testsuite.cpp \
    Dependencies/darkstyle/DarkStyle.cpp \
    Dependencies/darkstyle/framelesswindow/framelesswindow.cpp \
    Dependencies/darkstyle/framelesswindow/windowdragger.cpp \
    Core/histogram.cpp \
    Core/qcplinearcolormap.cpp \
    Core/Graph/userblock.cpp \
    Core/IO/blocksourcecodemanager.cpp

HEADERS += \
    Core/Graph/block.h \
    Core/Graph/edge.h \
    Core/Graph/graphwidget.h \
    Core/Graph/inputport.h \
    Core/Graph/mycustomblock.h \
    Core/Graph/outputport.h \
    Core/Graph/port.h \
    Core/UI/addblockdialog.h \
    Core/debug.h \
    Core/linearregression.h \
    Core/mainwindow.h \
    Core/plot.h \
    Core/utilities.h \
    Dependencies/qcustomplot-source/qcustomplot.h \
    Core/testsuite.h \
    Dependencies/darkstyle/DarkStyle.h \
    Dependencies/darkstyle/framelesswindow/framelesswindow.h \
    Dependencies/darkstyle/framelesswindow/windowdragger.h \
    Core/histogram.h \
    Core/qcplinearcolormap.h \
    Core/Graph/userblock.h \
    Core/IO/blocksourcecodemanager.h

FORMS += \
    Core/UI/addblockdialog.ui \
    Core/mainwindow.ui \
    Dependencies/darkstyle/framelesswindow/framelesswindow.ui

DISTFILES += \
    bg.svg

SUBDIRS += \
    JumboEagle.pro

INCLUDEPATH += Dependencies\

RESOURCES += \
    Dependencies/darkstyle/darkstyle.qrc \
    Dependencies/darkstyle/framelesswindow.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Dependencies/opencv-3.4.1/opencv/build/x64/vc14/lib/ -lopencv_world341
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Dependencies/opencv-3.4.1/opencv/build/x64/vc14/lib/ -lopencv_world341d
else:unix: LIBS += -L$$PWD/Dependencies/opencv-3.4.1/opencv/build/x64/vc14/lib/ -lopencv_world341

INCLUDEPATH += Dependencies/opencv-3.4.1/opencv/build/include
DEPENDPATH += Dependencies/opencv-3.4.1/opencv/build/include
