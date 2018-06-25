#include "customblock.h"
#include "utilities.h" // insideRect

namespace je {

CustomBlock::CustomBlock() : Block(){

}

CustomBlock::CustomBlock(int x, int y, int w, int h) : Block(x, y, w, h) {
    // In both cases, "this" gets upcasted to Block
    std::shared_ptr<InputPort> ip = std::make_shared<InputPort>(this);
    inputPorts.push_back(ip);
    std::shared_ptr<OutputPort> op = std::make_shared<OutputPort>(this);
    outputPorts.push_back(op);
}

CustomBlock::~CustomBlock()
{
    // Free up memory
    inputPorts.clear();
    outputPorts.clear();
    activePort = nullptr;
}

void CustomBlock::draw(QPainter *painter){

    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());

    // Draw main block
    // Set different brush colour if active block
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Write name inside block
    painter->drawText(rectangle, Qt::AlignCenter, getName());

    // Draw ports
    for(auto const &ip : inputPorts){
        ip->draw(painter);
    }
    for(auto const &op : outputPorts){
        op->draw(painter);
    }
}

clickType CustomBlock::mousePressEvent(QPoint point){
    // TODO: make this neater by adding helper function that checks whether point is in box
    if(insideRect(this, point)) // this, has the same interface as QRect
    {
        return clickType::block;
    }
    for(auto const &ip : inputPorts){
        if(insideRect(ip, point))
        {
            setActivePort(ip);
            return clickType::inPort;
        }
    }
    for(auto const &op : outputPorts){
        if(insideRect(op, point))
        {
            setActivePort(op);
            return clickType::outPort;
        }
    }
    return clickType::none;
}

void CustomBlock::setActivePort(std::shared_ptr<Port> port){
    activePort = port;
}

std::shared_ptr<Port> CustomBlock::getActivePort(){
    return activePort;
}

} // je
