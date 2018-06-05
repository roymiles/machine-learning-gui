#include "customblock.h"
#include "inputport.h"
#include "outputport.h"

CustomBlock::CustomBlock() : Block(){

}

CustomBlock::CustomBlock(int x, int y, int w, int h) : Block(x, y, w, h) {
    InputPort *ip = new InputPort(this); // "this" gets upcasted to Block
    ports.push_back(ip);
    OutputPort *op = new OutputPort(this); // "this" gets upcasted to Block
    ports.push_back(op);
}

void CustomBlock::draw(QPainter *painter){

    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());

    // Draw main block
    // Set different brush colour if active block
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Draw ports
    for(auto const &p : ports){
        p->draw(painter);
    }

    //QRect output(x + w, y + h/2 - portHeight/2, portWidth, portHeight); // Output
}
