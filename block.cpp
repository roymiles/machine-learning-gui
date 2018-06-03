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

    this->portWidth  = w / 4;
    this->portHeight = h / 4;

    active = false;
}

void Block::draw(QWidget *canvas)
{
    QRect rectangle(x, y, w, h);

    // Draw main block
    QPainter painter(canvas);
    // Set different brush colour if active block
    painter.fillRect(rectangle, Qt::white);
    painter.drawRect(rectangle);

    // Draw the input and outport ports
    QRect input(x - portWidth, y + h/2 - portHeight/2, portWidth, portHeight); // Input
    QRect output(x + w, y + h/2 - portHeight/2, portWidth, portHeight); // Output
    painter.fillRect(input, Qt::yellow);
    painter.drawRect(input);
    painter.fillRect(output, Qt::yellow);
    painter.drawRect(output);

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

QPoint Block::getInputPos()
{
   const int inputX = x - portWidth;
   const int inputY = y + h/2;
   QPoint centerPoint(inputX, inputY);

   return centerPoint;
}

QPoint Block::getOutputPos()
{
    const int outputX = x + w + portWidth;
    const int outputY = y + h/2;
    QPoint centerPoint(outputX, outputY);

    return centerPoint;
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


