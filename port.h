#ifndef PORT_H
#define PORT_H

#include <QPainter>

class Port
{
public:
    Port();
    virtual void draw(QPainter *painter) = 0;
};

#endif // PORT_H
