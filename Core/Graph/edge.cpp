#include "edge.h"

namespace je { namespace graph {

// If the draw function changes, the mousePressEvent logic will need to be updated
void Edge::draw(QPainter *painter)
{
    // At the moment, just draw a straight line from the start and to the end vertex

    // Get center of the output port of the first vertex
    QPoint outPoint = endPoints.first->getPorts().second->getCenter();

    // And similarly for the input port of the second vertex
    QPoint inPoint = endPoints.second->getPorts().first->getCenter();

    painter->drawLine(outPoint.x(), outPoint.y(), inPoint.x(), inPoint.y());
}

BlockPointer Edge::getStartVertex()
{
    return endPoints.first;
}

BlockPointer Edge::getEndVertex()
{
    return endPoints.second;
}

bool Edge::mousePressEvent(QPoint &point)
{
    /*
     * NOTE: the mousePressEvent is coupled closely to how the edge is drawn
     */

    /*
     *  At the moment, we have an edge connecting two ports/points x1,y1 -> x2,y2
     *  Need to find if point x,y is on this path (allow some margin of error)
     */
    int margin_of_error = 0;

    QPoint point1 = endPoints.first->getPorts().second->getCenter();
    QPoint point2 = endPoints.second->getPorts().first->getCenter();
    int x1 = point1.x();
    int x2 = point2.x();
    int y1 = point1.x();
    int y2 = point2.x();
    // The line function can be derived from (y2-y1) = m(x2-x1)

    // Check for division by zero
    if(x2 - x1 == 0)
        return false;

    int m = (y2 - y1) / (x2 - x1);

    // Now we know the gradient, can calculate the y-intercept (offset) c
    // y = mx + c
    int c = y1 - (m * x1);

    // Estimate for point.y
    // NOTE: The line does not extend to infinity, so need to bound estimate from x to [x1, x2]
    int x;
    if(x1 < x2)
    {
        if(point.x() < x1)
            x = x1;
        else if(point.x() > x2)
            x = x2;
        else
            x = point.x();
    }
    int y_est = (m * x) + c;

    qDebug() << "y = " << point.y() << ", y_est = " << y_est;

    // If y - y_est is less than margin of error, then assume we clicked on this edge
    if(std::abs(point.y() - y_est) <= margin_of_error)
        return true;
    else
        return false;

}

} } // graph, je
