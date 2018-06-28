#include "block.h"
#include "../debug.h"

#include <QPainter>
#include <QRect>

namespace je { namespace graph {

Block::Block() : x(0), y(0), w(50), h(50), tabIndex(-1)
{
}

Block::Block(int x, int y, int width, int height) : x(x), y(y), w(width), h(height), tabIndex(-1)
{
}

Block::~Block()
{
}

void Block::setX(int x)
{
    this->x = x;
}

void Block::setY(int y)
{
    this->y = y;
}

void Block::setPos(QPoint point)
{
    this->x = point.x();
    this->y = point.y();
}

int Block::getX() const
{
    return x;
}

int Block::getY() const
{
    return y;
}

int Block::getW() const
{
    return w;
}

int Block::getH() const
{
    return h;
}

void Block::setName(QString name)
{
    this->name = name;
}

const QString& Block::getName() const
{
    return this->name;
}

} } // graph, je
