#include "inputport.h"

InputPort::InputPort(Block *parentBlock)
{
    this->parentBlock = parentBlock;
    //active = false;
}


void InputPort::draw(QPainter *painter)
{
    const int w = parentBlock->getW() /4;
    const int h = parentBlock->getH()/4;
    const int x = parentBlock->getX() - w;
    const int y = parentBlock->getY() + parentBlock->getH()/2 - h/2;

    QRect rectangle(x, y, w, h);

    // Draw input port
    painter->fillRect(rectangle, Qt::yellow);
    painter->drawRect(rectangle);
}
