#include "edge.h"

namespace je { namespace graph {

void Edge::draw(QPainter *painter)
{
    // At the moment, just draw a straight line from the start and to the end vertex

    // Get center of the output port of the first vertex
    QPoint outPoint = endPoints.first->getPorts().second->getCenter();

    // And similarly for the input port of the second vertex
    QPoint inPoint = endPoints.first->getPorts().second->getCenter();

    painter->drawLine(outPoint.x(), outPoint.y(), inPoint.x(), inPoint.y());
}

BlockPointer Edge::getStartVertex()
{
    return endPoints.first;
}

BlockPointer Edge::getEndVertex()
{
    return endPoints.second;
}

} } // graph, je
