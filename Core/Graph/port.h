#ifndef PORT_H
#define PORT_H

#include <QPainter>
#include <memory>

namespace je { namespace graph {

class Port
{
public:
    Port() {}
    virtual void draw(QPainter *painter) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getW() const = 0;
    virtual int getH() const = 0;
    virtual QPoint getCenter() const = 0;
};

typedef std::shared_ptr<Port> PortPointer;

} } // graph, je

#endif // PORT_H
