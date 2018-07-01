#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "../block.h"

using namespace je::graph;

class MyCustomBlock : public iblock_t
{
public:
    MyCustomBlock();

    //int execute(int in) override;
};

#endif // MYCUSTOMBLOCK_H
