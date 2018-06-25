#include "edge.h"

namespace je {

Edge::Edge()
{

}

Edge::Edge(std::shared_ptr<OutputPort> start, std::shared_ptr<InputPort> end)
{
    this->start = start;
    this->end   = end;
}

void Edge::draw(QPainter *painter)
{
    painter->drawLine(start->getX(), start->getY(), end->getX(), end->getY());
}

} // je
