#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "userblock.h"

using namespace je;

class MyCustomBlock : public UserBlock
{
public:
    MyCustomBlock();
    MyCustomBlock(int x, int y, int width, int height);
};

#endif // MYCUSTOMBLOCK_H
