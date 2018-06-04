#ifndef CUSTOMBLOCK_H
#define CUSTOMBLOCK_H

#include <vector>
#include <QPainter>

#include "block.h"
#include "port.h"

// All user generated blocks are inherited from this

class CustomBlock : public Block
{
public:
    CustomBlock();
    CustomBlock(int x, int y, int width, int height);
    void draw(QPainter *painter);
private:
    std::vector<Port*> ports;
};

#endif // CUSTOMBLOCK_H
