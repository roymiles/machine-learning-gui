#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QPoint>
#include <string>
#include "port.h"

// Checks where a click takes place
enum clickType{
    inPort,
    outPort,
    block,
    none
};

class Block
{
public:
    Block();
    Block(int x, int y, int width, int height);

    virtual void draw(QPainter *painter) = 0;
    virtual clickType mousePressEvent(QPoint point) = 0;
    virtual void setActivePort(Port *port) = 0;
    virtual Port* getActivePort() = 0;

    void setX(int x);
    void setY(int y);
    void setPos(QPoint point);
    int getX();
    int getY();
    int getW();
    int getH();

    void setName(std::string name);
    std::string getName();

    // Returns true if the coordinates are inside this block
    bool insideBlock(QPoint point);

    // True if the block is being dragged
    bool active;

private:
    int x, y, w, h;
    std::string name;
};

#endif // BLOCK_H
