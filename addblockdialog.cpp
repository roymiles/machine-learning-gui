#include "addblockdialog.h"
#include "ui_addblockdialog.h"

#include <QDebug>
#include <iostream>

AddBlockDialog::AddBlockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBlockDialog)
{
    graphWidget = nullptr;
    ui->setupUi(this);
}

AddBlockDialog::~AddBlockDialog()
{
    delete ui;
}

void AddBlockDialog::on_AddBlockDialog_finished(int result)
{
    // Just before dialog closes, after either confirm or reject.
}

void AddBlockDialog::on_AddBlockConfirmButton_accepted()
{
    if(this->graphWidget != nullptr)
    {
        this->graphWidget->addBlock(ui->BlockNameLineEdit->text());
    }else{
        // Give error message
        qDebug() << "graphWidget is null";
    }

    this->close();
}

void AddBlockDialog::setGraphWidget(GraphWidget *graphWidget)
{
    this->graphWidget = graphWidget;
}

void AddBlockDialog::on_AddBlockConfirmButton_rejected()
{
    // Close dialog
    this->close();
}
