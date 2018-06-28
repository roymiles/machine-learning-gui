#include "addblockdialog.h"
#include "ui_addblockdialog.h"

#include <QDebug>
#include <QMessageBox>
#include "../IO/blocksourcecodemanager.h"
#include "../utilities.h"

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
        // Validate file name
        const QString fileName = ui->BlockNameLineEdit->text();
        if(isValidFileName(fileName))
        {
            this->graphWidget->addBlock(fileName);
            this->close();
        }else{
            // TODO: FIX THIS BUG (CRASHES APPLICATION)
            //QMessageBox msgBox;
            //msgBox.setText("Invalid block name."); // Give more detail...
            //msgBox.exec();

            // Don't close the add block dialog
            this->close();
        }
    }else{
        // Give error message
        qDebug() << "graphWidget is null";
        this->close();
    }
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
