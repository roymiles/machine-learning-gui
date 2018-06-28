#ifndef EDGE_H
#define EDGE_H

#include <QPainter>
#include <memory>
#include <utility> // std::pair, std::make_pair
#include "block.h"

namespace je { namespace graph {

class Edge
{
public:
    Edge() = delete;
    Edge(const std::pair<BlockPointer, BlockPointer> endPoints) : endPoints(endPoints) {}

    void draw(QPainter *painter);

private:
    // Can't change the end points once the edge is created
    const std::pair<BlockPointer, BlockPointer> endPoints;
};

} } // graph, je

#endif // EDGE_H
