#ifndef MYCUSTOMSOURCE_H
#define MYCUSTOMSOURCE_H

#include "../block.h"

using namespace je::graph;

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
        return 5;
    }
};

#endif // MYCUSTOMSOURCE_H
