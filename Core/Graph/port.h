#ifndef PORT_H
#define PORT_H

#include <QPainter>

namespace je { namespace graph {

class Port
{
public:
    Port();
    virtual void draw(QPainter *painter) = 0;
    const int getX() const;
    const int getY() const;
    const int getW() const;
    const int getH() const;
    QPoint getCenter() const;

    bool activePort;

protected:
    int x, y, w, h; // TODO: add setters
};

} } // graph, je

#endif // PORT_H
