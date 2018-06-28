#include "userblock.h"
#include "../utilities.h" // insideRect
#include "../IO/blocksourcecodemanager.h"

namespace je {

UserBlock::UserBlock() : Block(){
    inputPort = std::make_shared<InputPort>(this);
    outputPort = std::make_shared<OutputPort>(this);
}

UserBlock::UserBlock(int x, int y, int w, int h) : Block(x, y, w, h) {
    inputPort = std::make_shared<InputPort>(this);
    outputPort = std::make_shared<OutputPort>(this);
}

UserBlock::~UserBlock()
{
    // Free up memory
    inputPort = nullptr;
    outputPort = nullptr;
}

void UserBlock::draw(QPainter *painter){

    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());

    // Draw main block
    // Set different brush colour if active block
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Write name inside block
    painter->drawText(rectangle, Qt::AlignCenter, getName());

    // Draw ports
    inputPort->draw(painter);
    outputPort->draw(painter);
}

clickType UserBlock::mousePressEvent(QPoint &point){
    // TODO: make this neater by adding helper function that checks whether point is in box

    if(insideRect(this, point))
    {
        return clickType::block;
    }
    else if(insideRect(inputPort, point))
    {
        return clickType::inPort;
    }
    else if(insideRect(outputPort, point))
    {
        return clickType::outPort;
    }
    else
    {
        return clickType::none;
    }
}

QPoint UserBlock::getInputPortCenter()
{
    return inputPort->getCenter();
}

QPoint UserBlock::getOutputPortCenter()
{
    return outputPort->getCenter();
}


QWidget* UserBlock::loadTabWidget()
{
    // First time opening tab, so create an instance of the file manager
    if(blockSourceCodeManager == nullptr)
        blockSourceCodeManager = std::make_unique<io::BlockSourceCodeManager>(this->getName());

    // Attempt to load the source file. If file does not exist, create it
    if(!blockSourceCodeManager->loadSourceFile())
        blockSourceCodeManager->createSourceFile(); // Create the source file, build boiler plate code

    return blockSourceCodeManager->getContent();
}

} // je
