#include "addblockdialog.h"
#include "ui_addblockdialog.h"

#include <QDebug>
#include <QMessageBox>
#include "../IO/blocksourcecodemanager.h"
#include "../Utility/utilities.h"
#include "../Graph/blockutils.h"

namespace je { namespace ui {

using namespace utility;

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
        block_types selectedBlockType = (block_types)ui->blockTypeComboBox->currentIndex();
        data_types selectedDataType  = (data_types)ui->dataTypeComboBox->currentIndex();

        const QString blockName = ui->BlockNameLineEdit->text();
        if(!utility::isValidBlockName(blockName))
        {
            utility::inputDialog("Invalid block name.");
            this->close();
            return;
        }

        // block_factory returns a function for creating new blocks, hence () at end
        std::shared_ptr<IBlock> b = graph::block_factory[selectedBlockType]();
        graphWidget->addBlock(b, blockName);

        /*switch(selectedBlockType)
        {
            using namespace utility;
            using namespace graph;

            case block_types::BLOCK:
                typedef enum2blocktype<block_types::BLOCK, data_types::DOUBLE>::inner_type blocktype1;
                this->graphWidget->addBlock<blocktype1>(blockName);
                break;
            case block_types::SINK:
                typedef enum2blocktype<block_types::SINK, data_types::DOUBLE>::inner_type blocktype2;
                this->graphWidget->addBlock<blocktype2>(blockName);
                break;
            case block_types::SOURCE:
                typedef enum2blocktype<block_types::SOURCE, data_types::DOUBLE>::inner_type blocktype3;
                this->graphWidget->addBlock<blocktype3>(blockName);
                break;
            case block_types::LINEAR_REGRESSION:
                typedef enum2blocktype<block_types::LINEAR_REGRESSION, data_types::DOUBLE>::inner_type blocktype4;
                this->graphWidget->addBlock<blocktype4>(blockName);
                break;
        }*/

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
