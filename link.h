#ifndef LINK_H
#define LINK_H

#include "block.h"

class Link
{
public:
    Link();
    Link(Block *start, Block *end);

    void draw(QWidget *canvas);

private:
    Block *start;
    Block *end;
};

#endif // LINK_H
