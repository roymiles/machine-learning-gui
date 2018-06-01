#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <iostream>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    std::cout << "Width = " << width() << ", Height = " << height() << std::endl;
}

void GraphWidget::addBlock()
{
    Block *b = new Block(0, 0, 50, 50);

    blocks.push_back(b);

    this->update(); // Re-paints the canvas
}

void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);
    QPixmap pixmap("C:/Users/Roy/Documents/JumboEagle/bg.png");
    painter.drawPixmap(10,10,50,50, pixmap);

    //std::cout << "Painting" << std::endl;
    for(auto const &b : blocks)
    {
        b->draw(this);
    }
}

void GraphWidget::mousePressEvent(QMouseEvent* e)
{
    //std::cout << "Mouse press" << std::endl;
    // Check if clicking on a block
    for(auto const &b : blocks)
    {
        if(b->insideBlock(e->pos()))
        {
            activeBlock = b;
            activeBlock->active = true;
            break;
        }
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent* e)
{
    //std::cout << "Mouse move, x = " << e->pos().x() << ", y = " << e->pos().y() << std::endl;
    if(activeBlock != nullptr)
    {
        // Need to offset the position by half the width and height of the box
        QPoint p = e->pos();
        p.setX(p.x() - activeBlock->getW()/2);
        p.setY(p.y() - activeBlock->getH()/2);

        // Move the block
        activeBlock->setPos(p);
    }

    this->update();
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* e)
{
    //std::cout << "Mouse release" << std::endl;
    activeBlock->active = false;
    activeBlock = nullptr;
}
