#include "graphcontroller.h"

#include "debug.h"
#include <QPointF>
#include <QGraphicsRectItem>

#include <iostream> // remove

GraphController::GraphController(QGraphicsView *graphicsView)
{
    /*
     * Initialise the graphics view
     */

    view = graphicsView;

    scene = new GraphicsScene();

    view->setScene(scene);
}

void GraphController::addBlock()
{
    //QGraphicsRectItem *block = scene->addRect(0,0, 100, 100);
    Block *block = new Block();
    block->setRect(0, 0, 100, 100);
    block->setFlag(QGraphicsItem::ItemIsMovable);
    //block->setData(itemData_e::INDEX, );
    blocks.push_back(block);

    std::cout << "There are now " << blocks.size() << " blocks" << std::endl;
}
