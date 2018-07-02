#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "../block.h"

using namespace je::graph;

class MyCustomBlock : public Block<int>
{
public:
    MyCustomBlock();

    void init() override;
    int run(int in) override;
};

#endif // MYCUSTOMBLOCK_H
