#ifndef OUTPUTPORT_H
#define OUTPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

class OutputPort : public Port
{
public:
    OutputPort(Block *parentBlock);
    void draw(QPainter *painter);
private:
    Block *parentBlock;
};

#endif // OUTPUTPORT_H
