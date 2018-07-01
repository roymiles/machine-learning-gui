#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += opengl # Maybe dont need?
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

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
    Core/Graph/edge.cpp \
    Core/Graph/graphwidget.cpp \
    Core/Graph/inputport.cpp \
    Core/Graph/outputport.cpp \
    Core/Graph/Blocks/mycustomblock.cpp \
    Core/IO/blocksourcecodemanager.cpp \
    Core/Maths/histogram.cpp \
    Core/Maths/linearregression.cpp \
    Core/UI/addblockdialog.cpp \
    Core/Utility/utilities.cpp \
    Core/qcplinearcolormap.cpp \
    Dependencies/qcustomplot-source/qcustomplot.cpp \
    Core/main.cpp \
    Core/mainwindow.cpp \
    Core/Graph/iblock.cpp


HEADERS += \
    Core/Graph/edge.h \
    Core/Graph/graphwidget.h \
    Core/Graph/inputport.h \
    Core/Graph/outputport.h \
    Core/Graph/port.h \
    Core/Graph/Blocks/mycustomblock.h \
    Core/IO/blocksourcecodemanager.h \
    Core/Maths/histogram.h \
    Core/Maths/linearregression.h \
    Core/UI/addblockdialog.h \
    Core/Utility/debug.h \
    Core/Utility/plot.h \
    Core/Utility/utilities.h \
    Core/Graph/block.h \
    Dependencies/qcustomplot-source/qcustomplot.h \
    Core/mainwindow.h \
    Core/Graph/iblock.h \
    Core/Graph/blockutils.h


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
