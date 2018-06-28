#ifndef USERBLOCK_H
#define USERBLOCK_H

#include <vector>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <memory>

#include "block.h"
#include "port.h"
#include "inputport.h"
#include "outputport.h"
#include "../IO/blocksourcecodemanager.h"

namespace je { // Not in graph sub namespace to reduce user boilerplate code

/*
 * Generic block with one input and one output port. All user blocks must inherit from this.
 * This has a BlockSourceCodeManager widget that loads the text editor in a new tab with the source code of the block
 */

using namespace je::graph;

class UserBlock : public Block
{
public:
    UserBlock();
    UserBlock(int x, int y, int width, int height);
    ~UserBlock();

    // All user blocks have a standard look
    void draw(QPainter *painter) override;
    clickType mousePressEvent(QPoint &point) override;

    QPoint getInputPortCenter() override;
    QPoint getOutputPortCenter() override;

    std::shared_ptr<InputPort> inputPort;
    std::shared_ptr<OutputPort> outputPort;

    QWidget* loadTabWidget() override;

private:
    std::unique_ptr<io::BlockSourceCodeManager> blockSourceCodeManager;
};

} // je

#endif // USERBLOCK_H
