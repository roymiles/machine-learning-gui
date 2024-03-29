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
    Core/UI/addblockdialog.cpp \
    Core/Utility/utilities.cpp \
    Core/qcplinearcolormap.cpp \
    Dependencies/qcustomplot-source/qcustomplot.cpp \
    Core/main.cpp \
    Core/mainwindow.cpp \
    Core/Graph/iblock.cpp \
    Dependencies/darkstyle/framelesswindow/framelesswindow.cpp \
    Dependencies/darkstyle/framelesswindow/windowdragger.cpp \
    Dependencies/darkstyle/DarkStyle.cpp \
    Core/Graph/blockutils.cpp \
    Core/Components/IO/datamanager.cpp \
    Core/Components/IO/texteditor.cpp \
    Core/Components/Maths/Linear/ridgeregression.cpp


HEADERS += \
    Core/Graph/edge.h \
    Core/Graph/graphwidget.h \
    Core/Graph/inputport.h \
    Core/Graph/outputport.h \
    Core/Graph/port.h \
    Core/Graph/Blocks/mycustomblock.h \
    Core/UI/addblockdialog.h \
    Core/Utility/debug.h \
    Core/Utility/utilities.h \
    Core/Graph/block.h \
    Dependencies/qcustomplot-source/qcustomplot.h \
    Core/mainwindow.h \
    Core/Graph/iblock.h \
    Core/Graph/blockutils.h \
    Dependencies/darkstyle/framelesswindow/framelesswindow.h \
    Dependencies/darkstyle/framelesswindow/windowdragger.h \
    Dependencies/darkstyle/DarkStyle.h \
    Core/Graph/Blocks/mycustomsink.h \
    Core/Graph/Blocks/mycustomsource.h \
    Core/Graph/blockbase.h \
    Dependencies/matplotlibcpp/matplotlibcpp.h \
    Core/Graph/Blocks/linearregressionblock.h \
    Core/Graph/blockloader.h \
    Core/Components/IO/datamanager.h \
    Core/Components/Maths/Linear/regression.h \
    Core/Components/plot.h \
    Core/Components/IO/texteditor.h \
    Core/Components/Maths/Linear/ridgeregression.h


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

INCLUDEPATH += C:/Users/Roy/AppData/Local/Programs/Python/Python35/include
INCLUDEPATH += Dependencies/opencv-3.4.1/opencv/build/include
DEPENDPATH += Dependencies/opencv-3.4.1/opencv/build/include
