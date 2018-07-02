#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTabWidget>
#include <QString>
#include <vector>
#include <memory>
#include <string>
#include <utility> // std::pair
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>

#include "block.h"
#include "edge.h"
#include "port.h"

// TODO: The following includes should be seperated into a loader
#include "../Graph/Blocks/mycustomblock.h"
#include "../Graph/Blocks/mycustomsink.h"
#include "../Graph/Blocks/mycustomsource.h"

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

    // Add a block of type T (T inherits from Block and in turn IBlock)
    template<typename T>
    void GraphWidget::addBlock(QString name)
    {
        std::shared_ptr<IBlock> myBlock = std::make_shared<T>();
        vertex_t vertex = boost::add_vertex(myBlock, graph);

        qDebug() << "Attempting to add new block";
        qDebug() << "is_sink : " << T::is_sink();
        qDebug() << "is_source : " << T::is_source();
        qDebug() << source << sink;

        // Only allow at most one source and one sink
        if(T::is_sink())
        {
            if(!isNullDescriptor(sink))
            {
                boost::remove_vertex(vertex, graph);
                inputDialog("Too many sinks");
                return;
            }else{
                qDebug() << "Adding sink";
                sink = vertex;
            }
        }

        if(T::is_source())
        {
            if(!isNullDescriptor(source)){
                boost::remove_vertex(vertex, graph);
                inputDialog("Too many sources");
                return;
            }else{
                qDebug() << "Adding source";
                source = vertex;
            }
        }

        graph[vertex]->setName(name);
        qDebug() << "Added vertex " << name;
        qDebug() << "Num vertices = " << boost::num_vertices(graph);
        qDebug() << "Num edges = " << boost::num_edges(graph);

        this->update(); // Re-paints the canvas
    }

    std::shared_ptr<IBlock> getBlock(const vertex_t vertex);

    void run();

protected:
    void paintEvent(QPaintEvent*);

    // All the Qt mouse events
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

private:
    // Only allowed one sink and one source in the flow graph
    // The vertex of the source and sinks are remembered to
    // aid in the breadth first search
    vertex_t sink;
    vertex_t source;

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
