#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(OutputPort *start, InputPort *end)
{
    this->start = start;
    this->end   = end;
}

void Edge::draw(QPainter *painter)
{
    painter->drawLine(start->getX(), start->getY(), end->getX(), end->getY());
}
