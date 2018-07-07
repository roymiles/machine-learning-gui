#include "addblockdialog.h"
#include "ui_addblockdialog.h"

#include <QDebug>
#include <QMessageBox>
#include "../IO/blocksourcecodemanager.h"
#include "../Utility/utilities.h"

namespace je { namespace ui {

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
        // These are mapped to the block_type and data_type enums respectively
        auto selectedBlockType = ui->comboBox->currentIndex();
        auto selectedDataType  = 0; // TODO

        const QString blockName = ui->BlockNameLineEdit->text();
        if(!utility::isValidBlockName(blockName))
        {
            utility::inputDialog("Invalid block name.");
            this->close();
            return;
        }

        typedef utility::enum2blocktype<selectedBlockType, selectedDataType>::inner_type blocktype;
        this->graphWidget->addBlock<blocktype>(blockName);
        this->close();

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

} } // ui, je
