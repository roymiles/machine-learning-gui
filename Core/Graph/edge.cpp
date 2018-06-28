#include "edge.h"

namespace je { namespace graph {

void Edge::draw(QPainter *painter)
{
    // At the moment, just draw a straight line from the start and to the end vertex
    painter->drawLine(endPoints.first->getX(), endPoints.first->getY(), endPoints.second->getX(), endPoints.second->getY());
}

} } // graph, je
