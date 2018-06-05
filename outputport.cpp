#include "outputport.h"

OutputPort::OutputPort(Block *parentBlock)
{
    this->parentBlock = parentBlock;
}


void OutputPort::draw(QPainter *painter)
{
    const int w = parentBlock->getW() /4;
    const int h = parentBlock->getH()/4;
    const int x = parentBlock->getX() + parentBlock->getW();
    const int y = parentBlock->getY() + parentBlock->getH()/2 - h/2;

    QRect rectangle(x, y, w, h);

    // Draw output port
    painter->fillRect(rectangle, Qt::yellow);
    painter->drawRect(rectangle);
}
