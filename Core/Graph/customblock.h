#ifndef CUSTOMBLOCK_H
#define CUSTOMBLOCK_H

#include <vector>
#include <QPainter>
#include <QPoint>
#include <memory>

#include "block.h"
#include "port.h"
#include "inputport.h"
#include "outputport.h"

namespace je { // Not in graph sub namespace to reduce user boilerplate code

/***
 * Generic block with one input and one output port. All user blocks must inherit from this.
 ***/

using namespace je::graph;

class CustomBlock : public Block
{
public:
    CustomBlock();
    CustomBlock(int x, int y, int width, int height);
    ~CustomBlock();

    void draw(QPainter *painter) override;
    void setActivePort(std::shared_ptr<Port> port) override;
    std::shared_ptr<Port> getActivePort() override;
    clickType mousePressEvent(QPoint point) override;

    std::vector<std::shared_ptr<InputPort>> inputPorts;
    std::vector<std::shared_ptr<OutputPort>> outputPorts;
    std::shared_ptr<Port> activePort;
};

} // je

#endif // CUSTOMBLOCK_H
