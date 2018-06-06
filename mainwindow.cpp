#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <iostream>

#include "debug.h"
#include "addblockdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Add the widget elements that have been added graphically
    ui->setupUi(this);

    graphWidget = new GraphWidget(this);
    ui->gridLayout->addWidget(graphWidget);


}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    // Exit application if user presses ESC
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addBlock_clicked()
{
    std::cout << "Adding block" << std::endl;
    /*AddBlockDialog addBlockDialog;
    addBlockDialog.setModal(true);
    addBlockDialog.exec();*/

    graphWidget->addBlock("hi");
}

void MainWindow::on_zoomOut_clicked()
{
    graphWidget->zoomOut();
}

void MainWindow::on_zoomIn_clicked()
{
    graphWidget->zoomIn();
}
