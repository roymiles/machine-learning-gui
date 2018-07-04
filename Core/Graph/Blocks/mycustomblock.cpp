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
    //qDebug() << "Running MyCustomBlock";
    qDebug() << "Block received: " << in;
    return 5 * 5;
}
