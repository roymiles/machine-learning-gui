#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <vector>
#include "graphicsscene.h"
#include "block.h"

class GraphController
{
public:
    GraphController(QGraphicsView *graphicsView);

    // Add a block to the diagram
    void addBlock();

private:
    std::vector<Block*> blocks;

    GraphicsScene *scene;
    QGraphicsView *view;
};

#endif // GRAPHICSVIEW_H
