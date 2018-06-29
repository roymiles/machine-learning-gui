#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "../BlockTypes/customblock.h"

using namespace je;

class MyCustomBlock : public iblock_t
{
public:
    MyCustomBlock();

    //int execute(int in) override;
};

#endif // MYCUSTOMBLOCK_H
