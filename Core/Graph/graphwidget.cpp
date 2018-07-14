#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "inputport.h"
#include "outputport.h"
#include <QDebug>
#include <QMatrix>
#include <QPlainTextEdit>
#include "block.h"
#include "../Utility/utilities.h"

namespace je { namespace graph {

GraphWidget::GraphWidget(QWidget *parent, QTabWidget *tabWidget) : QWidget(parent)
{
    // Widget accepts focus by clicking or by tabbing. This ensures keyPressEvent works.
    setFocusPolicy(Qt::StrongFocus);

    setMouseTracking(true);
    curState = State::IDLE;
    this->tabWidget = tabWidget;
    this->drawingEdge = std::make_pair(G::null_vertex(), G::null_vertex());

    source = G::null_vertex();
    sink   = G::null_vertex();
    movingVertex = G::null_vertex();
}

/*
 *  All painting to the graph widget must be done within this function
 */
void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);

    // Does not work
    QPixmap pixmap("C:\\Users\\Roy\\Documents\\JumboEagle\\Resources\\bg.png");
    // Tile the background
    const int width = 50;
    const int height = 50;
    for(int x = 0; x < this->width(); x += width)
        for(int y = 0; y < this->height(); y += height)
            painter.drawPixmap(x, y, width, height, pixmap);

    // NOTE: The order of drawing is important. Edges should be drawn before (below) blocks
    // Draw all edges
    for(auto edge : boost::make_iterator_range(boost::edges(graph)))
    {
        if(activeEdge != boost::none)
        {
            // Highlight active edge
            if(edge == *activeEdge)
                painter.setPen(Qt::red);
        }

        graph[edge]->draw(&painter);

        if(activeEdge != boost::none)
        {
            // Back to default pen
            if(edge == *activeEdge)
                painter.setPen(Qt::black);
        }
    }

    // Draw all blocks (and internally the ports)
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {
    //for (auto vertex = boost::make_reverse_iterator(boost::vertices(graph)); vertex != my_vector.rend(); ++i ) {
        if(vertex == activeVertex)
            painter.setPen(Qt::red);

        graph[vertex]->draw(&painter);

        if(vertex == activeVertex)
            painter.setPen(Qt::black);
    }

    // If in the DRAWING state, want to draw from the previously clicked port to the mouse position
    if(curState == State::DRAWING_EDGE)
    {
        // Only one vertex is connected, either the start or the end point
        bool no_source = (drawingEdge.first == G::null_vertex());
        bool no_target = (drawingEdge.second == G::null_vertex());
        if(no_source && !no_target){
            // Draw from target (input port) to cursor
            painter.drawLine(graph[drawingEdge.second]->getPorts().first->getCenter(), cursorPos);
        }else if(!no_source && no_target){
            // Draw from source (output port) to cursor
            painter.drawLine(graph[drawingEdge.first]->getPorts().second->getCenter(), cursorPos);
        }
    }
}

/*
 * When pressing the mouse button, loop through all the blocks and check if clicking on the block itself,
 * or any of its ports.
 * If clicking on a block, want to be able to drag and move the block around
 * If clicking on a port (for the first time) want to enter the DRAWING state, where a line is drawn from the port to the mouse
 * Then, after clicking another port, create the link between these two ports.
 */
void GraphWidget::mousePressEvent(QMouseEvent* e)
{
    // Check if clicking on a block (or its ports)
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {

        bool hit = true; // Once a click event has been triggered (on either a block or a port), exit out of the loop
        block_part_e c = graph[vertex]->mousePressEvent(e->pos());
        switch(c)
        {
            case block_part_e::block:
                movingVertex = vertex;
                break;

            // The following click events have similar functionality, and so are grouped together
            // Can connect either way round. e.g. in to and out, or an out to an in
            case block_part_e::in_port:
            case block_part_e::out_port:

                // Set the start and end port depending on the click event
                if(c == block_part_e::in_port) {
                    drawingEdge.second = vertex;
                }else{
                    drawingEdge.first = vertex;
                }

                movingVertex = G::null_vertex();
                // Clicking on port for first time
                if(curState == State::IDLE){
                    curState = State::DRAWING_EDGE;
                    //setMouseTracking(true); // Trigger mouse event without mouse click when in drawing state
                }
                // Clicking on port for second time, making the edge
                else if(curState == State::DRAWING_EDGE){
                    curState = State::IDLE;
                    //setMouseTracking(false);

                    if(drawingEdge.first != G::null_vertex() && drawingEdge.second != G::null_vertex())
                    { // Only create the edge if we have both the input and out_port ports

                        // Verify the data types of the input and output ports
                        if(graph[drawingEdge.first]->getOutType() != graph[drawingEdge.second]->getInType())
                        {
                            // Data types do not match, so do not add the edge
                            utility::inputDialog("Block port data types do not match");
                            return;
                        }

                        // Edge accepts a pair of pointer to the start and end blocks (vertices)
                        std::pair<BlockPointer, BlockPointer> endPoints = std::make_pair(graph[drawingEdge.first], graph[drawingEdge.second]);
                        std::shared_ptr<Edge> edge = std::make_shared<Edge>(endPoints);

                        edge_t _e; bool _b;
                        boost::tie(_e, _b) = boost::add_edge(drawingEdge.first, drawingEdge.second, edge, graph);
                        vertex_t source = _e.m_source;
                        vertex_t target = _e.m_target;
                        qDebug() << "Added edge connecting " << graph[source]->getName() << " to " << graph[target]->getName();
                        qDebug() << "Num vertices = " << boost::num_vertices(graph);
                        qDebug() << "Num edges = " << boost::num_edges(graph);
                        // The edge has been created so clear previous start and end
                        drawingEdge.first = G::null_vertex();
                        drawingEdge.second = G::null_vertex();

                    }
                }
                break;

            case block_part_e::none:
                movingVertex = G::null_vertex();
                hit = false; // No click events triggered, go onto the next block
                break;
        }

        if(hit) break; // Once triggered a click event, exit the loop
    }

}

/*
 * If in the DRAWING state, update the cursorPos based on the current mouse position
 * If there is an active block (dragging and moving a block) then move this block to the mouse position
 */
void GraphWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(curState == State::DRAWING_EDGE)
    {
        cursorPos = e->pos();
        this->update(); // Re-draw canvas
    }

    if(movingVertex != G::null_vertex()) // Currently holding down mouse button on a block, so move it with the mouse
    {
        // Need to offset the position by half the width and height of the box
        QPoint p = e->pos();
        p.setX(p.x() - graph[movingVertex]->getW()/2);
        p.setY(p.y() - graph[movingVertex]->getH()/2);

        // Move the block
        graph[movingVertex]->setPos(p);

        // Redraw canvas
        this->update();

    }

    // If not in drawing state or if moving a block
    if(movingVertex == G::null_vertex() && curState != State::DRAWING_EDGE)
    {
        // Check if hovering over a port
        for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
        {
            // NOTE: cannot draw to screen outside draw() function
            block_part_e p = graph[vertex]->mousePressEvent(e->pos());
            graph[vertex]->mouseHoverEvent(p, e->pos());
        }
    }
}

/*
 * When mouse button is released remove movingVertex (no longer moving any box around)
 * If the mouse is over an edge or a block, set that block/edge to active
 */
void GraphWidget::mouseReleaseEvent(QMouseEvent* e)
{
    movingVertex = G::null_vertex();

    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {
        // If release mouse on the block or any of its ports, keep as active/clicked vertex
        if(graph[vertex]->mousePressEvent(e->pos()) != block_part_e::none)
        {
           activeVertex = vertex;
           this->update();
           return; // Do not need to check any others
        }
    }

    // Similarly for an edge
    // ...

    // If reached here, then mouse is not released on anything so clear the active/clicked vertex/edge
    activeVertex = G::null_vertex();
    activeEdge   = boost::none;

    this->update();
}

/*
 * When double clicking on a block, want to open the text editor for the block.
 */
void GraphWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {
        if(graph[vertex]->mousePressEvent(e->pos()) == block_part_e::block)
        {
            // Check if the source is not already open
            const int tabIndex = graph[vertex]->getTabIndex();
            if(tabIndex == -1)
            {
                // Not in tab
                auto widget = graph[vertex]->tabWidget();
                this->tabWidget->addTab(widget, graph[vertex]->getName());
                const int i = this->tabWidget->count(); // Total number of tabs open
                graph[vertex]->setTabIndex(i-1); // Update the tab index
                this->tabWidget->setCurrentIndex(i-1);
            }else{
                // Already in a tab, so set it as the active tab
                this->tabWidget->setCurrentIndex(tabIndex);
            }

            break;
        }
    }
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            if(activeVertex != G::null_vertex())
            {
                if(activeVertex == source)
                    source = G::null_vertex();
                else if(activeVertex == sink)
                    sink = G::null_vertex();

                // Now remove the vertex
                boost::remove_vertex(activeVertex, graph);
            }
            break;
        //default:
            // Call base
    }

    this->update();
}

void GraphWidget::zoomIn()
{
    /*zoomX += 0.1;
    zoomY += 0.1;
    this->update();*/
    qDebug() << "Zooming disabled";
}

void GraphWidget::zoomOut()
{
    /*zoomX -= 0.1;
    zoomY -= 0.1;
    this->update();*/
    qDebug() << "Zooming disabled";
}

std::shared_ptr<IBlock> GraphWidget::getBlock(const vertex_t vertex)
{
    return graph[vertex];
}

void GraphWidget::run()
{
    if(sink == G::null_vertex() || source == G::null_vertex()){
        utility::inputDialog("Must have one source and one sink");
        return;
    }

    // Validate the edges
    // ...

    // Run init on all blocks (initialise all blocks)
    qDebug() << "init...";
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
        graph[vertex]->init();

    //while(graph[source]->isFinished())

    // Go through each vertex and execute its function.
    // The output of a preceeding vertex is fed into the next vertex
    //void* source_out = graph[source].run();
    typename G::out_edge_iterator ei, ei_end;
    vertex_t current_node = source;
    boost::any out, prev_out;
    // Run through all the vertices untill a sink is found
    bool at_sink = false;
    while(true)
    {
        // NOTE: the return void* is allocated using malloc and so must be freed
        //       when no longer being used

        auto t1 = std::chrono::system_clock::now();
        // Run the current block
        if(current_node == source) {
            out = graph[current_node]->run_v(prev_out);
        } else if(current_node == sink) {
            graph[current_node]->run_v(prev_out);
            at_sink = true; // Reached the end
        } else {
            out = graph[current_node]->run_v(prev_out);
        }
        auto t2 = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = t2-t1;
        //qDebug() << "t = " << elapsed_seconds.count();
        graph[current_node]->setExecutionTime(elapsed_seconds);

        // This is so can do timing calculations before breaking out of loop
        if(at_sink)
            break;

        // Pass timing details to block
        //graph[current_node]->elapsed_times.push_back(t2 - t1);

        // Move onto next block
        boost::tie(ei, ei_end) = boost::out_edges(current_node, graph);
        //auto source = boost::source(*ei, graph);
        auto target = boost::target(*ei, graph);
        current_node = target;

        prev_out = out;
    }

    // e.g. To update the displayed execution times on the blocks
    this->update();

}



} } // graph, je
