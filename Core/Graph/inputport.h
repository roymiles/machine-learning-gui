#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>
#include <memory>

namespace je { namespace graph {

class InputPort : public Port
{
public:
    InputPort() = delete;
    InputPort(const Block* parentBlock) : parentBlock(parentBlock) {}
    void draw(QPainter *painter) override;
private:
    const Block* parentBlock;
};

} } // graph, je

#endif // INPUTPORT_H
