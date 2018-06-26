#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "customblock.h"

using namespace je;

class MyCustomBlock : public CustomBlock
{
public:
    MyCustomBlock();
    MyCustomBlock(int x, int y, int width, int height);
};

#endif // MYCUSTOMBLOCK_H
