#include "graphicsscene.h"
#include <QDebug>
#include <QGraphicsItem>

#include "debug.h"
#include <iostream>

#include "graphcontroller.h" // remove

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QImage *image = new QImage("bg.png");
    if(image->isNull())
    {
        this->setBackgroundBrush(Qt::gray);
        Debug::Log("Unable to set background tiling for graphics scene");
    } else {
        QBrush *brush = new QBrush(*image);
        this->setBackgroundBrush(*brush);
    }

}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{


    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{


    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{


    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    // Release click
    QList<QGraphicsItem *> graphicsItems = items(mouseEvent->scenePos());
    if(!graphicsItems.isEmpty()) // If no items are at this position
    {
        qDebug() << "here u go " << graphicsItems.at(0)->data(itemData_e::INDEX);
        Debug::Log("Clicked on box");
    }

    // Check which object is selected
    //QGraphicsItem *item = this->itemAt(mouseEvent->pos(), QTransform());

    //Debug::Log(item->data(0));
    //std::cout << item->data(0) << std::endl;

    //QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
