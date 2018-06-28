#ifndef OUTPUTPORT_H
#define OUTPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>
#include <memory>

namespace je { namespace graph {

class OutputPort : public Port
{
public:
    OutputPort() = delete;
    OutputPort(const Block* parentBlock) : parentBlock(parentBlock) {}
    void draw(QPainter *painter) override;
private:
    const Block* parentBlock;
};

} } // graph, je

#endif // OUTPUTPORT_H
