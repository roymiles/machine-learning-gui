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

    // Default dimensions
    x = 50;
    y = 50;
    w = 100;
    h = 100;
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

void IBlock::getRect(QRect &rect) const
{
    rect.setX(x);
    rect.setY(y);
    rect.setWidth(w);
    rect.setHeight(h);
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

void IBlock::addExecutionTime(std::chrono::duration<double> time)
{
    executionTimes.push_back(time);
}

} } // graph, je
