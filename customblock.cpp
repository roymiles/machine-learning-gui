#include "customblock.h"

CustomBlock::CustomBlock() : Block(){

}

CustomBlock::CustomBlock(int x, int y, int w, int h) : Block(x, y, w, h) {
    InputPort *ip = new InputPort(this); // "this" gets upcasted to Block
    inputPorts.push_back(ip);
    OutputPort *op = new OutputPort(this); // "this" gets upcasted to Block
    outputPorts.push_back(op);
}

void CustomBlock::draw(QPainter *painter){

    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());

    // Draw main block
    // Set different brush colour if active block
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

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
    if(point.x() > this->getX() && point.y() > this->getY() && point.x() < this->getX() + this->getW() && point.y() < this->getY() + this->getH())
    {
        return clickType::block;
    }
    for(auto const &ip : inputPorts){
        if(point.x() > ip->getX() && point.y() > ip->getY() && point.x() < ip->getX() + ip->getW() && point.y() < ip->getY() + ip->getH())
        {
            setActivePort(ip);
            return clickType::inPort;
        }
    }
    for(auto const &op : outputPorts){
        if(point.x() > op->getX() && point.y() > op->getY() && point.x() < op->getX() + op->getW() && point.y() < op->getY() + op->getH())
        {
            setActivePort(op);
            return clickType::outPort;
        }
    }
    return clickType::none;
}

void CustomBlock::setActivePort(Port* port){
    activePort = port;
}

Port* CustomBlock::getActivePort(){
    return activePort;
}
