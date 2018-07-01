#include "inputport.h"
#include "block.h"

namespace je { namespace graph {

void InputPort::draw(QPainter *painter, QColor color)
{
    QRect rectangle(getX(), getY(), getW(), getH());

    // Draw input port
    painter->fillRect(rectangle, color);
    painter->drawRect(rectangle);
}

int InputPort::getX() const
{
    return parentBlock->getX() - this->getW();
}

int InputPort::getY() const
{
    return parentBlock->getY() + parentBlock->getH()/2 - this->getH()/2;
}

int InputPort::getW() const
{
    return parentBlock->getW() / 4;
}

int InputPort::getH() const
{
    return parentBlock->getH() / 4;
}

QPoint InputPort::getCenter() const
{
    return QPoint(getX(), getY());
}

} } // graph, je
