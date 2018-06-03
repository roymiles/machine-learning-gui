#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QPoint>
#include <string>

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

    QPoint getInputPos();
    QPoint getOutputPos();

    void setName(std::string name);
    std::string getName();

    // Returns true if the coordinates are inside this block
    bool insideBlock(QPoint point);

    bool active;

private:
    int x, y, w, h;
    int portWidth, portHeight;

    std::string name;
};

#endif // BLOCK_H
