#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <iostream>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    std::cout << "Width = " << width() << ", Height = " << height() << std::endl;
}

void GraphWidget::addBlock(std::string name)
{
    Block *b = static_cast<Block*>(new MyCustomBlock(100, 100, 100, 100));
    b->setName(name);

    blocks.push_back(b);

    // Expand the size of the adjacency Mat

    this->update(); // Re-paints the canvas
}

void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);
    QPixmap pixmap("Resources/bg.png");
    //painter.drawLine(0, 0, 20, 20);
    // Tile the background
    const int width = 50;
    const int height = 50;
    for(int x = 0; x < this->width(); x += width)
        for(int y = 0; y < this->height(); y += height)
            painter.drawPixmap(x, y, width, height, pixmap);

    //std::cout << "Painting" << std::endl;
    for(auto const &b : blocks)
    {
        b->draw(&painter);
    }

//    // TEST
//    if(blocks.size() == 2)
//    {
//        QPainter painter2(this);
//        //painter2.drawLine(blocks[0]->getX(), blocks[0]->getY(), blocks[1]->getX(), blocks[1]->getY());
//        painter2.drawLine(blocks[0]->getOutputPos(), blocks[1]->getInputPos());
//    }
}

void GraphWidget::mousePressEvent(QMouseEvent* e)
{
    //std::cout << "Mouse press" << std::endl;
    // Check if clicking on a block
    for(auto const &b : blocks)
    {
//        if(b->insideBlock(e->pos()))
//        {
//            activeBlock = b;
//            activeBlock->active = true;
//            break;
//        }
        switch(b->mousePressEvent(e->pos())){
            case clickType::block:
                activeBlock = b;
                activeBlock->active = true;
                break;
            case clickType::inPort:
                std::cout << "Clicked input port" << std::endl;
                break;
            case clickType::outPort:
                std::cout << "Clicked output port" << std::endl;
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
    if(activeBlock != nullptr)
    {
        activeBlock->active = false;
        activeBlock = nullptr;
    }
}
