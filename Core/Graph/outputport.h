#ifndef OUTPUTPORT_H
#define OUTPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

namespace je {

class OutputPort : public Port
{
public:
    OutputPort(Block *parentBlock);
    void draw(QPainter *painter) override;
private:
    Block *parentBlock;
};

} // je

#endif // OUTPUTPORT_H
