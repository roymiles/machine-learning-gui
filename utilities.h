#ifndef UTILITIES_H
#define UTILITIES_H

#include <QRect>
#include <QPoint>

template<typename T>
inline bool insideRect(T &rect, QPoint &point)
{
    return
    point.x() > rect->getX() &&  // Point is on right hand side of leftmost rectangle edge
    point.y() > rect->getY() &&  // Point is below the topmost rectangle edge
    point.x() < rect->getX() + rect->getW() &&  // Point is on the left of the rightmost rectangle edge
    point.y() < rect->getY() + rect->getH();    // Point is above the bottommost rectangle edge
}

#endif // UTILITIES_H
