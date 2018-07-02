#include "mycustomsink.h"

MyCustomSink::MyCustomSink() : Sink<int>()
{

}

void MyCustomSink::init()
{
    qDebug() << "Initializing MyCustomSink";
}

void_t MyCustomSink::run(int in)
{
    return void_t{};
}
