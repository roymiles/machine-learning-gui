#ifndef OUTPUTPORT_H
#define OUTPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

namespace je { namespace graph {

class OutputPort : public Port
{
public:
    OutputPort(Block *parentBlock);
    void draw(QPainter *painter) override;
private:
    Block *parentBlock;
};

} } // graph, je

#endif // OUTPUTPORT_H
