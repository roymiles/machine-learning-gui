#include "block.h"
#include "debug.h"

#include <QPainter>
#include <QRect>

Block::Block()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;

    active = false;
}

Block::Block(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;

    active = false;
}

void Block::draw(QWidget *canvas)
{
    QRect rectangle(x, y, w, h);

    QPainter painter(canvas);
    // Set different brush colour if active block
    painter.drawRect(rectangle);
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

int Block::getX()
{
    return x;
}

int Block::getY()
{
    return y;
}

int Block::getW()
{
    return w;
}

int Block::getH()
{
    return h;
}

bool Block::insideBlock(QPoint point)
{
    // Boundary check to see if coordinates lie inside the block
    if(point.x() > this->x && point.y() > this->y && point.x() < this->x + this->w && point.y() < this->y + this->h)
    {
        return true;
    }else{
        return false;
    }
}


