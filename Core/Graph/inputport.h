#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

namespace je { namespace graph {

class InputPort : public Port
{
public:
    InputPort(Block *parentBlock);
    void draw(QPainter *painter) override;
private:
    Block *parentBlock;
};

} } // graph, je

#endif // INPUTPORT_H
