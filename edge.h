#ifndef EDGE_H
#define EDGE_H

#include <QPainter>
#include "inputport.h"
#include "outputport.h"

class Edge
{
public:
    Edge();
    Edge(OutputPort *start, InputPort *end);

    void draw(QPainter *painter);

private:
    OutputPort *start;
    InputPort *end;
};

#endif // EDGE_H
