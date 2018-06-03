#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <string>

#include "block.h"
#include "link.h"

#include <opencv2/opencv.hpp>

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

  // This matrix describes all the connections between blocks
  //Matb adjacencyMat;
  //cv::Mat a;

  // The current block that is being moved around, see mousePressEvent
  Link* link;
  Block* activeBlock;

};

#endif // GRAPHWIDGET_H
