#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <string>

#include "block.h"
#include "mycustomblock.h" //TODO: can't include every type of block
#include "edge.h"
#include "port.h"

//#include <opencv2/opencv.hpp>

enum state {
    IDLE,
    DRAWING
};

class GraphWidget : public QWidget
{
  Q_OBJECT

public:
    GraphWidget(QWidget *parent=0);

    void addBlock(std::string name);
    // Connect two blocks together. Output of block1 is connected to input of block2
    void connectBlocks(Block *block1, Block *block2);

protected:
    void paintEvent(QPaintEvent*);

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);

    void drawConnection();

private:
    std::vector<Block*> blocks;
    std::vector<Edge*> edges;

    // The current block that is being moved around, see mousePressEvent
    Block* activeBlock;

    state curState;

    // This is for drawing a link between two ports
    OutputPort *start;
    InputPort *end;

    // Mouse position
    QPoint cursorPos;

};

#endif // GRAPHWIDGET_H
