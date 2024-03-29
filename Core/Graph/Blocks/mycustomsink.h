#ifndef MYCUSTOMSINK_H
#define MYCUSTOMSINK_H

#include "../block.h"

using namespace je::graph;

template<typename T>
class sink_run_impl
{
public:
    static boost::blank run(T in)
    {
        qFatal("The non-specialised sink_run_impl functions should not be used.");

        // Won't actually ever make it here, this just keeps compiler happy
        boost::blank b;
        return b;
    }
};

template<>
class sink_run_impl<int>
{
public:
    static boost::blank run(int in)
    {
        qDebug() << "Output = " << in;

        boost::blank b;
        return b;
    }
};

template<>
class sink_run_impl<double>
{
public:
    static boost::blank run(double in)
    {
        qDebug() << "Output = " << in;

        boost::blank b;
        return b;
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

    boost::blank run(T in) override
    {
        return sink_run_impl<T>::run(in);
    }
};

#endif // MYCUSTOMSINK_H
