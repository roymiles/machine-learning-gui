#ifndef PORT_H
#define PORT_H

#include <QPainter>

class Port
{
public:
    Port();
    virtual void draw(QPainter *painter) = 0;
    int getX();
    int getY();
    int getW();
    int getH();
    QPoint getCenter();

    bool activePort;

protected:
    int x, y, w, h; // TODO: add setters
};

#endif // PORT_H
