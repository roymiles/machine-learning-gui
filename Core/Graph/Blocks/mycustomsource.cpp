#include "mycustomsource.h"

MyCustomSource::MyCustomSource() : Source<int>()
{

}

void MyCustomSource::init()
{
    qDebug() << "Initializing MyCustomSource";
}

int MyCustomSource::run(void_t in)
{
    return 5.0;
}
