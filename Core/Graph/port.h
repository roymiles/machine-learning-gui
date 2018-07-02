#ifndef PORT_H
#define PORT_H

#include <QPainter>
#include <memory>
#include <QColor>

namespace je { namespace graph {

class Port
{
public:
    Port() {}
    // The draw function takes in a color which is dependant on the input/output type
    virtual void draw(QPainter *painter, QColor color) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getW() const = 0;
    virtual int getH() const = 0;

    /*
     * This is the point at which the edges are drawn from
     * This is not the geometric center of the shape
     */
    virtual QPoint getCenter() const = 0;
};

typedef std::shared_ptr<Port> PortPointer;

} } // graph, je

#endif // PORT_H
