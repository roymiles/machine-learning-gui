#ifndef EDGE_H
#define EDGE_H

#include <QPainter>
#include <memory>
#include "inputport.h"
#include "outputport.h"

namespace je { namespace graph {

class Edge
{
public:
    Edge();
    Edge(std::shared_ptr<OutputPort> start, std::shared_ptr<InputPort> end);

    void draw(QPainter *painter);

private:
    std::shared_ptr<OutputPort> start;
    std::shared_ptr<InputPort> end;
};

} } // graph, je

#endif // EDGE_H
