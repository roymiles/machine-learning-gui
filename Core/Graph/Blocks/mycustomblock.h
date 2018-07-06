#ifndef MYCUSTOMBLOCK_H
#define MYCUSTOMBLOCK_H

#include "../block.h"

using namespace je::graph;

template<typename T>
class MyCustomBlock : public Block<T>
{
public:
    MyCustomBlock() : Block<T>()
    {

    }

    void init() override
    {
        qDebug() << "Initializing MyCustomBlock";
    }

    T run(T in) override
    {
        return in * 5;
    }
};

#endif // MYCUSTOMBLOCK_H
