#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <vector>

#include "block.h"

class GraphWidget : public QWidget
{
  Q_OBJECT

public:
    GraphWidget(QWidget *parent=0);

    void addBlock();

protected:
  void paintEvent(QPaintEvent*);

  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseMoveEvent(QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);

private:
  std::vector<Block*> blocks;

  // The current block that is being moved around, see mousePressEvent
  Block* activeBlock;

};

#endif // GRAPHWIDGET_H
