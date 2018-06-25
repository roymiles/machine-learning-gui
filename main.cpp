#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
//#include <opencv2/opencv.hpp>

//#include "DarkStyle.h"
//#include "framelesswindow.h"

#include <iostream>
#include <string>
#include "linearregression.h"
#include <boost/numeric/ublas/matrix.hpp>

using namespace je;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    using namespace boost::numeric::ublas;

    testInvertMatrix();

    // Example with a feature size of 1 (p = 1)
    // y = 5x -> B = 5
    const int N = 3; // # Outputs
    const int P = 1; // Dimensions

    matrix<double> X(N, P+1); // [N x (p+1)] -> [3 x 2]
    // Row 1
    X(0, 0) = 1;
    X(0, 1) = 1;
    // Row 2
    X(1, 0) = 1;
    X(1, 1) = 2;
    // Row 3
    X(2, 0) = 1;
    X(2, 1) = 3;

    matrix<double> Y(N, 1); // # outputs = 3 -> [3 x 1]
    Y(0, 0) = 5;
    Y(1, 0) = 10;
    Y(2, 0) = 15;

    // Function approximation
    auto f = new LinearRegression<double>(Y, X);

    // Input X=2
    matrix<double> in(1, P+1);
    in(0, 0) = 1; // Probably easier to assume this will always be 1?
    in(0, 1) = 2;

    matrix<double> A = f->calculate(in);
    std::cout << "y = f(2) = " << A << std::endl;


    // Input X=20
    in(0, 0) = 1;
    in(0, 1) = 20;

    A = f->calculate(in);
    std::cout << "y = f(20) = " << A << std::endl;

    // Style our application with custom dark style
    //app.setStyle(new DarkStyle);

    // Create frameless window (and set windowState or title)
    //FramelessWindow framelessWindow;
    //framelessWindow.setWindowState(Qt::WindowMaximized);
    //framelessWindow.setWindowTitle("test title");
    //framelessWindow.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));

    // Create our mainwindow instance
    MainWindow *mainWindow = new MainWindow;

    // Add the mainwindow to our custom frameless window
    //framelessWindow.setContent(mainWindow);
    //framelessWindow.show();

    mainWindow->show();

    return app.exec();
}
