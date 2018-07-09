#ifndef MYCUSTOMSINK_H
#define MYCUSTOMSINK_H

#include "../block.h"

using namespace je::graph;

template<typename T>
class sink_run_impl
{
public:
    static T run(T in)
    {
        qFatal("The non-specialised sink_run_impl functions should not be used.");
        return static_cast<T>(0);
    }
};

template<>
class sink_run_impl<int>
{
public:
    static void run(int in)
    {
        qDebug() << "Output = " << in;
    }
};

template<>
class sink_run_impl<double>
{
public:
    static void run(double in)
    {
        qDebug() << "Output = " << in;
    }
};


template<typename T>
class MyCustomSink : public Sink<T>
{
public:
    MyCustomSink() : Sink<T>() {}
    ~MyCustomSink() {}

    void init() override
    {
        //qDebug() << "Initializing MyCustomSink";
    }

    void run(T in) override
    {
        sink_run_impl<T>::run(in);
    }
};

#endif // MYCUSTOMSINK_H
