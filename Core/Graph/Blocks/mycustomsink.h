#ifndef MYCUSTOMSINK_H
#define MYCUSTOMSINK_H

#include "../block.h"

using namespace je::graph;

template<typename T>
class MyCustomSink : public Sink<T>
{
public:
    MyCustomSink() : Sink<T>() {}
    ~MyCustomSink() {}

    void init() override
    {
        qDebug() << "Initializing MyCustomSink";
    }

    void run(T in) override
    {
        qDebug() << "Output = " << in;
    }
};

#endif // MYCUSTOMSINK_H
