#include "port.h"

namespace je {

Port::Port()
{
    activePort = false;
}

const int Port::getX() const
{
    return x;
}

const int Port::getY() const
{
    return y;
}

const int Port::getW() const
{
    return w;
}

const int Port::getH() const
{
    return h;
}

QPoint Port::getCenter() const
{
    return QPoint(x + w/2, y + h/2);
}

} // je
