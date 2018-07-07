#ifndef MYCUSTOMSOURCE_H
#define MYCUSTOMSOURCE_H

#include "../block.h"

using namespace je::graph;

template<typename T>
class source_run_impl
{
public:
    static T run(T in)
    {
        qFatal("The non-specialised source_run_impl functions should not be used.");
        return static_cast<T>(0);
    }
};

template<>
class source_run_impl<int>
{
public:
    static int run()
    {
        return 5;
    }
};

template<typename T>
class MyCustomSource : public Source<T>
{
public:
    MyCustomSource() : Source<T>() {}
    ~MyCustomSource() {}

    void init() override
    {
        qDebug() << "Initializing MyCustomSource";
    }

    T run() override
    {
        return source_run_impl<int>::run();
    }
};

#endif // MYCUSTOMSOURCE_H
