#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <iostream>

#include "debug.h"
#include "addblockdialog.h"
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Add the widget elements that have been added graphically
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(true);
    graphWidget = new GraphWidget(this, ui->tabWidget);
    ui->tabWidget->addTab(graphWidget, "Flow graph");

    je::testLinearRegression(ui->tabWidget);
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
    AddBlockDialog addBlockDialog;
    addBlockDialog.setGraphWidget(this->graphWidget); // Inject graph widget so that dialog can call addBlock
    addBlockDialog.setModal(true);
    addBlockDialog.exec();
}

void MainWindow::on_zoomOut_clicked()
{
    graphWidget->zoomOut();
}

void MainWindow::on_zoomIn_clicked()
{
    graphWidget->zoomIn();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // Check for memory leaks...
    // Set the associated block tabIndex to -1
    graphWidget->getBlock(index)->tabIndex = -1;

    ui->tabWidget->removeTab(index);
}
