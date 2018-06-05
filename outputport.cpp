#include "outputport.h"

OutputPort::OutputPort(Block *parentBlock)
{
    this->parentBlock = parentBlock;
}


void OutputPort::draw(QPainter *painter)
{
    w = parentBlock->getW() /4;
    h = parentBlock->getH()/4;
    x = parentBlock->getX() + parentBlock->getW();
    y = parentBlock->getY() + parentBlock->getH()/2 - h/2;

    QRect rectangle(x, y, w, h);

    // Draw output port
    painter->fillRect(rectangle, Qt::yellow);
    painter->drawRect(rectangle);
}
