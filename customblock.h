#ifndef CUSTOMBLOCK_H
#define CUSTOMBLOCK_H

#include <vector>
#include <QPainter>
#include <QPoint>

#include "block.h"
#include "port.h"
#include "inputport.h"
#include "outputport.h"

/***
 * Generic block with one input and one output port. All user blocks must inherit from this.
 ***/

class CustomBlock : public Block
{
public:
    CustomBlock();
    CustomBlock(int x, int y, int width, int height);
    void draw(QPainter *painter) override;
    clickType mousePressEvent(QPoint point);

private:
    std::vector<InputPort*> inputPorts;
    std::vector<OutputPort*> outputPorts;
};

#endif // CUSTOMBLOCK_H
