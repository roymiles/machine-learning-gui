#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include "inputport.h"
#include "outputport.h"
#include <QDebug>
#include <QMatrix>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(false);
    curState = state::IDLE;
    std::cout << "Width = " << width() << ", Height = " << height() << std::endl;
    start = nullptr;
    end   = nullptr;
    zoomX = 1.0;
    zoomY = 1.0;
    translateX = 1;
    translateY = 1;
}

void GraphWidget::addBlock(std::string name)
{
    Block *b = static_cast<Block*>(new MyCustomBlock(100, 100, 100, 100));
    b->setName(name);

    blocks.push_back(b);

    this->update(); // Re-paints the canvas
}

void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);

    QMatrix matrix;
    matrix.translate(translateX, translateY);
    matrix.scale(zoomX, zoomY);
    painter.setMatrix(matrix);

    QPixmap pixmap(":/Resources/bg.png");
    // Tile the background
    const int width = 50;
    const int height = 50;
    for(int x = 0; x < this->width(); x += width)
        for(int y = 0; y < this->height(); y += height)
            painter.drawPixmap(x, y, width, height, pixmap);

    // Draw ports and blocks
    for(auto const &b : blocks)
    {
        b->draw(&painter);
    }
    // Draw all edges
    for(auto const &e : edges)
    {
        e->draw(&painter);
    }

    if(curState == state::DRAWING){
        if(start == nullptr && end != nullptr){
            painter.drawLine(end->getCenter(), cursorPos);
        }
        else if (end == nullptr && start != nullptr) {
            painter.drawLine(start->getCenter(), cursorPos);
        }
    }
}

void GraphWidget::mousePressEvent(QMouseEvent* e)
{
    std::cout << "Mouse press" << std::endl;

    // Check if clicking on a block
    for(size_t i = 0; i < blocks.size(); i++)
    {
        bool hit = true;
        switch(blocks[i]->mousePressEvent(e->pos()))
        {
            case clickType::block:
                activeBlock = &(blocks[i]);
                break;
            case clickType::inPort:
                activeBlock = nullptr;
                // Clicking on port for first time
                if(curState == state::IDLE){
                    curState = state::DRAWING;
                    setMouseTracking(true); // Trigger mouse event without mouse click when in drawing state
                    end = (InputPort*)blocks[i]->getActivePort();
                    std::cout << "Start drawing line" << std::endl;
                }
                // Clicking on port for second time, making the edge
                else if(curState == state::DRAWING){
                    curState = state::IDLE;
                    setMouseTracking(false);
                    end = (InputPort*)blocks[i]->getActivePort();

                    if(start != nullptr && end != nullptr){
                        Edge* edge = new Edge(start, end);
                        edges.push_back(edge);

                        // The edge has been created so clear previous start and end
                        start = nullptr;
                        end = nullptr;
                    }
                    std::cout << "End drawing line" << std::endl;
                }
                break;
            case clickType::outPort:
                activeBlock = nullptr;
                if(curState == state::IDLE){
                    curState = state::DRAWING;
                    setMouseTracking(true); // Trigger mouse event without mouse click when in drawing state
                    start = (OutputPort*)blocks[i]->getActivePort();
                    std::cout << "Start drawing line" << std::endl;
                }
                else if(curState == state::DRAWING){
                    curState = state::IDLE;
                    setMouseTracking(false);
                    start = (OutputPort*)blocks[i]->getActivePort(); // TODO: downcasting is bad

                    if(start != nullptr && end != nullptr){
                        Edge* edge = new Edge(start, end);
                        edges.push_back(edge);

                        // The edge has been created so clear previous start and end
                        start = nullptr;
                        end = nullptr;
                    }
                    std::cout << "End drawing line" << std::endl;
                }
                break;
            case clickType::none:
                curState = state::PANNING;
                panPos = e->pos(); // Reference pos
                activeBlock = nullptr;
                hit = false;
                break;
        }

        if(hit) break;
    }

}

void GraphWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(curState == state::DRAWING)
    {
        cursorPos = e->pos();
        this->update(); // Re-draw canvas
    }

    //std::cout << "Mouse move, x = " << e->pos().x() << ", y = " << e->pos().y() << std::endl;
    if(activeBlock != nullptr)
    {
        // Need to offset the position by half the width and height of the box
        QPoint p = e->pos();
        p.setX(p.x() - (*activeBlock)->getW()/2);
        p.setY(p.y() - (*activeBlock)->getH()/2);

        // Move the block
        (*activeBlock)->setPos(p);

        // Redraw canvas
        this->update();

    }

    if(curState == state::PANNING)
    {
        // Panning the canvas

        // Update the translation based on how much panned from click
        translateX -= (panPos.x() - e->pos().x());
        translateY -= (panPos.y() - e->pos().y());

        panPos = e->pos(); // Update panning reference

        this->update();
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* e)
{
    //std::cout << "Mouse release" << std::endl;
    if(activeBlock != nullptr)
    {
        std::cout << (*activeBlock)->getName() << std::endl;
        activeBlock = nullptr;
    }

    if(curState == state::PANNING)
    {
        // Exit out of the panning state
        curState = state::IDLE;
    }
}

void GraphWidget::zoomIn()
{
    zoomX += 0.1;
    zoomY += 0.1;
    this->update();
}

void GraphWidget::zoomOut()
{
    zoomX -= 0.1;
    zoomY -= 0.1;
    this->update();
}
