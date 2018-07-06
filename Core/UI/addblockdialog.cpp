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
        auto selectedBlockType = ui->comboBox->currentIndex();

        const QString blockName = ui->BlockNameLineEdit->text();
        if(!utility::isValidBlockName(blockName))
        {
            utility::inputDialog("Invalid block name.");
            this->close();
            return;
        }

        switch(selectedBlockType)
        {
        case BlockTypes::BLOCK:
            this->graphWidget->addBlock<MyCustomBlock<double>>(blockName);
            this->close();
            break;
        case BlockTypes::SOURCE:
            this->graphWidget->addBlock<MyCustomSource<double>>(blockName);
            this->close();
            break;
        case BlockTypes::SINK:
            this->graphWidget->addBlock<MyCustomSink<double>>(blockName);
            this->close();
            break;
        case BlockTypes::LINEAR_REGRESSION:
            this->graphWidget->addBlock<LinearRegressionBlock<double>>(blockName);
            this->close();
            break;
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

} } // ui, je
