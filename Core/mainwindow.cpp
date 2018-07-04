#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <iostream>

#include "Utility/debug.h"
#include "UI/addblockdialog.h"
#include "Utility/utilities.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Add the widget elements that have been added graphically
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(true);
    graphWidget = new je::graph::GraphWidget(this, ui->tabWidget);
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
    // Show add block dialog. This handles all the types of blocks that can be added to the graph
    je::AddBlockDialog addBlockDialog;
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

/*
 * Breaks if close any other type of tab
 * Not all tabs will be text editors! (editable_t blocks)
 */
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // Set the associated block tabIndex to -1
    graphWidget->getBlock(index)->setTabIndex(-1);
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_runButton_clicked()
{
    graphWidget->run();
}
