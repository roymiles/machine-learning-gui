#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QPoint>

class Block
{
public:
    Block();
    Block(int x, int y, int width, int height);

    void draw(QWidget *canvas);

    void setX(int x);
    void setY(int y);
    void setPos(QPoint point);
    int getX();
    int getY();
    int getW();
    int getH();

    // Returns true if the coordinates are inside this block
    bool insideBlock(QPoint point);

    bool active;

private:
    int x, y, w, h;
};

#endif // BLOCK_H
