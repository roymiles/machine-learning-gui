#include "mycustomblock.h"

MyCustomBlock::MyCustomBlock() : Block<int>()
{

}

void MyCustomBlock::init()
{
    qDebug() << "Initializing MyCustomBlock";
}

int MyCustomBlock::run(int in)
{
    qDebug() << "Running MyCustomBlock";
    return 5.0;
}
