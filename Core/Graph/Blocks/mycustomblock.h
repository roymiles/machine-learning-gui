#pragma once

#include "../block.h"

using namespace je::graph;

template<typename T>
class block_run_impl
{
public:
    static T run(T in)
    {
        qFatal("The non-specialised block_run_impl functions should not be used.");
        return static_cast<T>(0); // aka null, just to make compiler happy
    }
};

template<>
class block_run_impl<int>
{
public:
    static int run(int in)
    {
        return 5 * in;
    }
};


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
        return block_run_impl<T>::run(in);
    }
};
