#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>

#include "debug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gc = new GraphController(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addBlock_clicked()
{
    Debug::Log("Button clicked");

    gc->addBlock();
}
