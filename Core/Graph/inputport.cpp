#include "inputport.h"

namespace je {

InputPort::InputPort(Block *parentBlock)
{
    this->parentBlock = parentBlock;
}


void InputPort::draw(QPainter *painter)
{
    w = parentBlock->getW() /4;
    h = parentBlock->getH() /4;
    x = parentBlock->getX() - w;
    y = parentBlock->getY() + parentBlock->getH()/2 - h/2;

    QRect rectangle(x, y, w, h);

    // Draw input port
    painter->fillRect(rectangle, Qt::yellow);
    painter->drawRect(rectangle);
}

} // je
