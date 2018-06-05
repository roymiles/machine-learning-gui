#include "port.h"

Port::Port()
{
    activePort = false;
}

int Port::getX()
{
    return x;
}

int Port::getY()
{
    return y;
}

int Port::getW()
{
    return w;
}

int Port::getH()
{
    return h;
}

QPoint Port::getCenter(){
    return QPoint(x + w/2, y + h/2);
}
