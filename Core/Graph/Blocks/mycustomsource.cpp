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
    qDebug() << "Running MyCustomSource";
    return 5.0;
}
