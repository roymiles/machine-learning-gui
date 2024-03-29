#ifndef INPUTPORT_H
#define INPUTPORT_H

#include "port.h"
#include "block.h"
#include <QPainter>
#include <memory>

namespace je { namespace graph {

class IBlock;

class InputPort : public Port
{
public:
    InputPort() = delete;
    InputPort(const IBlock* parentBlock) : parentBlock(parentBlock) {}
    void draw(QPainter *painter, QColor color) override;

    int getX() const override;
    int getY() const override;
    int getW() const override;
    int getH() const override;
    QPoint getCenter() const override;

private:
    const IBlock* parentBlock;
};

} } // graph, je

#endif // INPUTPORT_H
