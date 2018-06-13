#include "graphwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "inputport.h"
#include "outputport.h"
#include <QDebug>
#include <QMatrix>
#include <QPlainTextEdit>

GraphWidget::GraphWidget(QWidget *parent, QTabWidget *tabWidget) : QWidget(parent)
{
    setMouseTracking(false);
    curState = state::IDLE;
    //std::cout << "Width = " << width() << ", Height = " << height() << std::endl;
    start = nullptr;
    end   = nullptr;
    zoomX = 1.0;
    zoomY = 1.0;
    translateX = 1;
    translateY = 1;
    this->tabWidget = tabWidget;
}

void GraphWidget::addBlock(QString name, std::unique_ptr<FileManager> fileManager)
{
    qDebug() << "Block name = " << name;
    // Probably lots of unnecessary copying, which can be optimised out
    std::shared_ptr<MyCustomBlock> block = std::make_shared<MyCustomBlock>(100, 100, 100, 100);
    block->setName(name);
    block->setFileManager(std::move(fileManager));

    blocks.push_back(block);

    this->update(); // Re-paints the canvas
}

/*
 *  All painting to the graph widget must be done within this function
 */
void GraphWidget::paintEvent(QPaintEvent* e)
{
    // Draw the background
    QPainter painter(this);

    //QMatrix matrix;
    //matrix.translate(translateX, translateY);
    //matrix.scale(zoomX, zoomY);
    //painter.setMatrix(matrix);

    QPixmap pixmap(":/Resources/bg.png");
    // Tile the background
    const int width = 50;
    const int height = 50;
    for(int x = 0; x < this->width(); x += width)
        for(int y = 0; y < this->height(); y += height)
            painter.drawPixmap(x, y, width, height, pixmap);

    // Draw ports and blocks
    for(auto const &b : blocks)
    {
        b->draw(&painter);
    }
    // Draw all edges
    for(auto const &e : edges)
    {
        e->draw(&painter);
    }

    // If in the DRAWING state, want to draw from the previously clicked port to the mouse position
    if(curState == state::DRAWING){
        if(start == nullptr && end != nullptr){
            painter.drawLine(end->getCenter(), cursorPos);
        }
        else if (end == nullptr && start != nullptr) {
            painter.drawLine(start->getCenter(), cursorPos);
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
    // Check if clicking on a block
    for(auto const &block : blocks)
    {
        bool hit = true; // Once a click event has been triggered (on either a block or a port), exit out of the loop
        clickType c = block->mousePressEvent(e->pos());
        switch(c)
        {
            case clickType::block:
                activeBlock = block;
                break;

            // The following click events have similar functionality, and so are grouped together
            case clickType::inPort:
            case clickType::outPort:

                // Set the start and end port depending on the click event
                if(c == clickType::inPort)
                {
                    // Downcasting could be avoided?
                    end   = std::static_pointer_cast<InputPort>(block->getActivePort());
                }else{
                    start = std::static_pointer_cast<OutputPort>(block->getActivePort());
                }

                activeBlock = nullptr;
                // Clicking on port for first time
                if(curState == state::IDLE){
                    curState = state::DRAWING;
                    setMouseTracking(true); // Trigger mouse event without mouse click when in drawing state
                }
                // Clicking on port for second time, making the edge
                else if(curState == state::DRAWING){
                    curState = state::IDLE;
                    setMouseTracking(false);

                    if(start != nullptr && end != nullptr){ // Only create the edge, if we have both the input and outport ports
                        std::unique_ptr<Edge> edge = std::make_unique<Edge>(start, end);
                        edges.push_back(std::move(edge));

                        // The edge has been created so clear previous start and end
                        start = nullptr;
                        end   = nullptr;
                    }
                }
                break;

            case clickType::none:
                //curState = state::PANNING;
                //panPos = e->pos(); // Reference pos
                activeBlock = nullptr;
                hit = false; // No click events triggered, go onto the next block
                break;
        }

        if(hit) break;
    }

}

/*
 * If in the DRAWING state, update the cursorPos based on the current mouse position
 * If there is an active block (dragging and moving a block) then move this block to the mouse position
 */
void GraphWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(curState == state::DRAWING)
    {
        cursorPos = e->pos();
        this->update(); // Re-draw canvas
    }

    //std::cout << "Mouse move, x = " << e->pos().x() << ", y = " << e->pos().y() << std::endl;
    if(activeBlock != nullptr)
    {
        // Need to offset the position by half the width and height of the box
        QPoint p = e->pos();
        p.setX(p.x() - activeBlock->getW()/2);
        p.setY(p.y() - activeBlock->getH()/2);

        // Move the block
        activeBlock->setPos(p);

        // Redraw canvas
        this->update();

    }

    /*if(curState == state::PANNING)
    {
        // Panning the canvas

        // Update the translation based on how much panned from click
        translateX -= (panPos.x() - e->pos().x());
        translateY -= (panPos.y() - e->pos().y());

        panPos = e->pos(); // Update panning reference

        this->update();
    }*/
}

/*
 * When releasing the mouse button, remove any active blocks.
 */
void GraphWidget::mouseReleaseEvent(QMouseEvent* e)
{
    //std::cout << "Mouse release" << std::endl;
    if(activeBlock != nullptr)
    {
        qDebug() << activeBlock->getName();
        activeBlock = nullptr;
    }

    /*if(curState == state::PANNING)
    {
        // Exit out of the panning state
        curState = state::IDLE;
    }*/
}

/*
 * When double clicking on a block, want to open the text editor for the block.
 */
void GraphWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    //std::cout << "Doubling clicking" << std::endl;
    for(auto const &block : blocks)
    {
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

// Is a look necessary? any alternatives?
std::shared_ptr<Block> GraphWidget::getBlock(const int index)
{
    for(auto &block : blocks)
        if(block->tabIndex == index) return block;

    return nullptr;
}
