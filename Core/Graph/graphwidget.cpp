#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "inputport.h"
#include "outputport.h"
#include <QDebug>
#include <QMatrix>
#include <QPlainTextEdit>
#include "../utilities.h"

namespace je { namespace graph {

GraphWidget::GraphWidget(QWidget *parent, QTabWidget *tabWidget) : QWidget(parent)
{
    setMouseTracking(false);
    curState = State::IDLE;
    this->tabWidget = tabWidget;
    this->drawingEdge = std::make_pair(nullDescriptor(), nullDescriptor());
}

void GraphWidget::addBlock(QString name)
{
    /*
     * Adds a user generated block
     */
    qDebug() << "Block name = " << name;

    std::shared_ptr<Block> myBlock = std::make_shared<MyCustomBlock>();
    Vertexd vertex = boost::add_vertex(myBlock, graph);
    graph[vertex]->setName(name);

    this->update(); // Re-paints the canvas
}

/*
 *  All painting to the graph widget must be done within this function
 */
void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);

    QPixmap pixmap("Resources/bg.png");
    // Tile the background
    const int width = 50;
    const int height = 50;
    for(int x = 0; x < this->width(); x += width)
        for(int y = 0; y < this->height(); y += height)
            painter.drawPixmap(x, y, width, height, pixmap);

    // Draw all blocks (and internally the ports)
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {
        graph[vertex]->draw(&painter);
    }

    // Draw all edges
    for(auto edge : boost::make_iterator_range(boost::edges(graph)))
    {
        graph[edge]->draw(&painter);
    }

    // If in the DRAWING state, want to draw from the previously clicked port to the mouse position
    if(curState == State::DRAWING_EDGE){
        // Only one vertex is connected, either the start or the end point
        bool firstNull = isNullDescriptor(drawingEdge.first);
        bool secondNull = isNullDescriptor(drawingEdge.second);
        if(firstNull && !secondNull){
            painter.drawLine(graph[drawingEdge.second]->getOutputPortCenter(), cursorPos);
        }else if (!firstNull && secondNull) {
            painter.drawLine(graph[drawingEdge.first]->getInputPortCenter(), cursorPos);
        }
    }
}

/*
 * When pressing the mouse button, loop through all the blocks and check if clicking on the block itself,
 * or any of its ports.
 * If clicking on a block, want to be able to drag and move the block around
 * If clicking on a port (for the first time) want to enter the DRAWING state, where a line is drawn from the port to the mouse
 * Then, after clicking another port, create the link between these two ports.
 *
 * Another loop is for checking if the mouse press is on an edge
 */
void GraphWidget::mousePressEvent(QMouseEvent* e)
{
    // Check if clicking on a block (or its ports)
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {

        bool hit = true; // Once a click event has been triggered (on either a block or a port), exit out of the loop
        clickType c = graph[vertex]->mousePressEvent(e->pos());
        switch(c)
        {
            case clickType::block:
                clickedVertex = vertex;
                break;

            // The following click events have similar functionality, and so are grouped together
            // Can connect either way round. e.g. in to and out, or an out to an in
            case clickType::inPort:
            case clickType::outPort:

                // Set the start and end port depending on the click event
                if(c == clickType::inPort){
                    drawingEdge.second = vertex;
                }else{
                    drawingEdge.first = vertex;
                }

                clearDescriptor(clickedVertex);
                // Clicking on port for first time
                if(curState == State::IDLE){
                    curState = State::DRAWING_EDGE;
                    setMouseTracking(true); // Trigger mouse event without mouse click when in drawing state
                }
                // Clicking on port for second time, making the edge
                else if(curState == State::DRAWING_EDGE){
                    curState = State::IDLE;
                    setMouseTracking(false);

                    if(isNullDescriptor(drawingEdge.first) && isNullDescriptor(drawingEdge.second)){ // Only create the edge if we have both the input and outport ports
                        // Edge accepts a pair of pointer to the start and end blocks (vertices)
                        std::pair<BlockPointer, BlockPointer> endPoints = std::make_pair(graph[drawingEdge.first], graph[drawingEdge.second]);
                        std::unique_ptr<Edge> edge = std::make_unique<Edge>(endPoints);
                        boost::add_edge(drawingEdge.first, drawingEdge.second, graph);

                        // The edge has been created so clear previous start and end
                        clearDescriptor(drawingEdge.first);
                        clearDescriptor(drawingEdge.second);
                    }
                }
                break;

            case clickType::none:
                clearDescriptor(clickedVertex);
                hit = false; // No click events triggered, go onto the next block
                break;
        }

        if(hit) break; // Once triggered a click event, exit the loop
    }

    // Check if clicked on an edge
    for(auto edge : boost::make_iterator_range(boost::edges(graph)))
    {
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

    if(!isNullDescriptor(clickedVertex)) // Currently holding down mouse button on a block, so move it with the mouse
    {
        // Need to offset the position by half the width and height of the box
        QPoint p = e->pos();
        p.setX(p.x() - graph[clickedVertex]->getW()/2);
        p.setY(p.y() - graph[clickedVertex]->getH()/2);

        // Move the block
        graph[clickedVertex]->setPos(p);

        // Redraw canvas
        this->update();

    }
}

/*
 * When releasing the mouse button, remove any active blocks.
 */
void GraphWidget::mouseReleaseEvent(QMouseEvent* e)
{
    // TODO NEED TO CHECK IF clickedVertex exists in graph (no overflow). Checking if invalid is not enough
    if(!isNullDescriptor(clickedVertex))
    {
        qDebug() << graph[clickedVertex]->getName();
        clearDescriptor(clickedVertex);
    }
}

/*
 * When double clicking on a block, want to open the text editor for the block.
 */
void GraphWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    for(auto vertex : boost::make_iterator_range(boost::vertices(graph)))
    {
        if(graph[vertex]->mousePressEvent(e->pos()) == clickType::block)
        {
            this->tabWidget->addTab(graph[vertex]->loadTabWidget(), graph[vertex]->getName());

        }
        /*
        if(block->mousePressEvent(e->pos()) == clickType::block)
        {
            // Check if the source is not already open
            const int tabIndex = block->tabIndex;
            if(tabIndex == -1)
            {
                // Not in a tab
                if(block->loadSource())
                {
                    QPlainTextEdit* textEdit = block->getSource();
                    this->tabWidget->addTab(textEdit, block->getName());
                    const int i = this->tabWidget->count(); // Total number of tabs open
                    block->tabIndex = i-1; // Update the tab index
                    this->tabWidget->setCurrentIndex(i-1);
                }

            }else{
                // Already in a tab, so set it as the active tab
                this->tabWidget->setCurrentIndex(tabIndex);
            }
            break;
        }
        */
    }
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

std::shared_ptr<Block> GraphWidget::getBlock(const Vertexd vertex)
{
    return graph[vertex];
}

} } // graph, je
