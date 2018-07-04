#include "mycustomsource.h"

MyCustomSource::MyCustomSource() : Source<int>()
{

}

void MyCustomSource::init()
{
    qDebug() << "Initializing MyCustomSource";
}

int MyCustomSource::run()
{
    //qDebug() << "Running MyCustomSource";
    qDebug() << "Input = " << 5.0;
    return 5.0;
}
