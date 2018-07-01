#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "../block.h"

using namespace je::graph;

class MyCustomBlock : public test_t
{
public:
    MyCustomBlock();

    void init() override;
    double run(int in) override
    {
        return 5.0;
    }
};

#endif // MYCUSTOMBLOCK_H
