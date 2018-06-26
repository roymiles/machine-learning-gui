#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTabWidget>
#include <QString>
#include <vector>
#include <memory>
//#include <string> Use QString instead of std::string, as more restrictive on encoding

#include "block.h"
#include "mycustomblock.h" //TODO: can't include every type of block
#include "edge.h"
#include "port.h"
#include "../IO/filemanager.h"

//#include <opencv2/opencv.hpp>

namespace je { namespace graph {

enum state {
    IDLE,
    DRAWING
    //PANNING
};

class GraphWidget : public QWidget
{
  Q_OBJECT

public:
    GraphWidget(QWidget *parent=0, QTabWidget *tabWidget=0); // Takes in tabWidget, because need graphWidget to add new tabs and stuff

    void addBlock(QString name, std::unique_ptr<io::FileManager> fileManager);

    void zoomIn();
    void zoomOut();

    std::shared_ptr<Block> getBlock(const int index);

protected:
    void paintEvent(QPaintEvent*);

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

private:
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Edge>> edges;

    // The current block that is being moved around, see mousePressEvent
    std::shared_ptr<Block> activeBlock;

    state curState;

    // This is for drawing a link between two ports
    std::shared_ptr<OutputPort> start;
    std::shared_ptr<InputPort> end;

    // The last position for panning reference
    //QPoint panPos;

    // Mouse position for when in the DRAWING state. Will draw from a port to this point
    QPoint cursorPos;

    float zoomX, zoomY;
    int translateX, translateY;

    QTabWidget *tabWidget;

    std::unique_ptr<io::FileManager> fileManager;

};

} } // graph, je

#endif // GRAPHWIDGET_H
