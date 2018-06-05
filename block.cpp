#include "block.h"
#include "debug.h"

#include <QPainter>
#include <QRect>

Block::Block()
{
    x = 0;
    y = 0;
    w = 50;
    h = 50;

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


void Block::setName(std::string name)
{
    this->name = name;
}

std::string Block::getName()
{
    return this->name;
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


