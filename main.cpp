#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

//#include "DarkStyle.h"
//#include "framelesswindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
