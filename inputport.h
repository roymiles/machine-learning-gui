#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>

namespace je {

class InputPort : public Port
{
public:
    InputPort(Block *parentBlock);
    void draw(QPainter *painter) override;
private:
    Block *parentBlock;
};

} // je

#endif // INPUTPORT_H
