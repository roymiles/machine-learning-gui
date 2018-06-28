#include "outputport.h"

namespace je { namespace graph {

void OutputPort::draw(QPainter *painter)
{
    QRect rectangle(getX(), getY(), getW(), getH());

    // Draw input port
    painter->fillRect(rectangle, Qt::red);
    painter->drawRect(rectangle);
}

int OutputPort::getX() const
{
    return parentBlock->getX() + parentBlock->getW();
}

int OutputPort::getY() const
{
    return parentBlock->getY() + parentBlock->getH()/2 - this->getH()/2;
}

int OutputPort::getW() const
{
    return parentBlock->getW() / 4;
}

int OutputPort::getH() const
{
    return parentBlock->getH() / 4;
}

QPoint OutputPort::getCenter() const
{
    return QPoint(getX(), getY());
}

} } // graph, je
