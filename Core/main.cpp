#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
//#include <opencv2/opencv.hpp>

#include <darkstyle/DarkStyle.h>
#include <darkstyle/framelesswindow/framelesswindow.h>

#include <iostream>
#include <string>
#include "Components/Maths/Linear/regression.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <qcustomplot-source/qcustomplot.h>
#include <opencv2/core.hpp>

using namespace je;

//#define DARK_STYLE

int main(int argc, char *argv[])
{
    cv::Mat a;
    QApplication app(argc, argv);

    // Create our mainwindow instance
    MainWindow *mainWindow = new MainWindow;

#ifdef DARK_STYLE
    // Style our application with custom dark style
    app.setStyle(new DarkStyle);

    // Create frameless window (and set windowState or title)
    FramelessWindow framelessWindow;
    framelessWindow.setWindowTitle("Jumbo Eagle");
    framelessWindow.setWindowIcon(app.style()->standardIcon(QStyle::SP_DesktopIcon));

    // Add the mainwindow to our custom frameless window
    framelessWindow.setContent(mainWindow);
    framelessWindow.show();
#else
    mainWindow->show();
#endif

    return app.exec();
}
