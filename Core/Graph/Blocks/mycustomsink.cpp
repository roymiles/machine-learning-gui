#include "mycustomsink.h"

MyCustomSink::MyCustomSink() : Sink<int>()
{

}

void MyCustomSink::init()
{
    qDebug() << "Initializing MyCustomSink";
}

void MyCustomSink::run(int in)
{
    //qDebug() << "Running MyCustomSink";
    qDebug() << "Output = " << in;
}
