#include "mycustomblock.h"

MyCustomBlock::MyCustomBlock() : CustomBlock()
{

}


int MyCustomBlock::execute(int in)
{
     return 5 * in;
}
