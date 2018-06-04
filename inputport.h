#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

class InputPort : public Port
{
public:
    InputPort(Block *parentBlock);
    void draw(QPainter *painter);

private:
    Block *parentBlock;
};

#endif // INPUTPORT_H
