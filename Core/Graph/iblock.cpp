#include "iblock.h"
#include "inputport.h"
#include "outputport.h"

namespace je { namespace graph {

IBlock::IBlock(bool has_input, bool has_output)
{
    ports.first = nullptr;
    ports.second = nullptr;

    if(has_input)
        ports.first = std::make_shared<InputPort>(this);

    if(has_output)
        ports.second = std::make_shared<OutputPort>(this);

    tabIndex = -1;
}

IBlock::~IBlock()
{
}

void IBlock::setX(int x)
{
    this->x = x;
}

void IBlock::setY(int y)
{
    this->y = y;
}

void IBlock::setPos(QPoint &point)
{
    this->x = point.x();
    this->y = point.y();
}

int IBlock::getX() const
{
    return x;
}

int IBlock::getY() const
{
    return y;
}

int IBlock::getW() const
{
    return w;
}

int IBlock::getH() const
{
    return h;
}

std::pair<PortPointer, PortPointer> IBlock::getPorts() const
{
    return ports;
}

void IBlock::setName(QString name)
{
    this->name = name;
}

const QString& IBlock::getName() const
{
    return this->name;
}

void IBlock::setTabIndex(int tabIndex)
{
    this->tabIndex = tabIndex;
}

int IBlock::getTabIndex() const
{
    return tabIndex;
}

} } // graph, je
