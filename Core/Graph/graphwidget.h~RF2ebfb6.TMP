#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTabWidget>
#include <QString>
#include <vector>
#include <memory>
#include <string>
#include <utility> // std::pair, std::make_pair
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>

#include "block.h"
#include "Blocks/mycustomblock.h" //TODO: can't include every type of block, need some loader .h
#include "edge.h"
#include "port.h"

namespace je { namespace graph {

enum State {
    IDLE,
    DRAWING_EDGE
};

// See: http://blog.hostilefork.com/boost-graph-templates-not-crazy/
// Graph type, defines the properties of the adjacency list
typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::directedS,
                              std::shared_ptr<IBlock>, // Vertex
                              std::shared_ptr<Edge>
                              > GraphType;
// For a vector container, these will be an unsigned integer index
typedef boost::graph_traits<GraphType> G;
typedef G::vertex_descriptor vertex_t;
typedef G::edge_descriptor edge_t;

class GraphWidget : public QWidget
{
  Q_OBJECT

public:
    GraphWidget(QWidget *parent=0, QTabWidget *tabWidget=0); // Takes in tabWidget, because need graphWidget to add new tabs and stuff

    void zoomIn();
    void zoomOut();

    void addBlock(QString name);
    std::shared_ptr<IBlock> getBlock(const vertex_t vertex);

protected:
    void paintEvent(QPaintEvent*);

    // All the Qt mouse events
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

private:
    GraphType graph; // Boost graph data type

    // The block that has been clicked on (before the mouse button has been released)
    vertex_t clickedVertex;

    State curState;

    // This is for drawing a link between two ports
    // Once this pair is filled up with 2 vertices, a corresponding edge will be added and the pair will be cleared
    std::pair<vertex_t, vertex_t> drawingEdge;

    // Mouse position for when in the DRAWING state. Will draw from a port to this point
    QPoint cursorPos;

    QTabWidget *tabWidget;

};

} } // graph, je

#endif // GRAPHWIDGET_H
