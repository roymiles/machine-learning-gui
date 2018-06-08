#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QPoint>
#include <QString>
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

    void setName(QString name);
    QString getName();

private:
    int x, y, w, h;
    QString name;
};

#endif // BLOCK_H
