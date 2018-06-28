#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QPoint>
#include <QString>
#include <QTextEdit>
#include <memory>
#include "port.h"
#include "../IO/blocksourcecodemanager.h"

namespace je { namespace graph {

// Checks where a click takes place
enum clickType{
    inPort,
    outPort,
    block,
    none
};

/*
 * Characteristic of all block types, including user generated and our own blocks
 */
class Block
{
public:
    Block();
    Block(int x, int y, int width, int height);
    ~Block();

    virtual void draw(QPainter *painter) = 0;
    virtual clickType mousePressEvent(QPoint &point) = 0;

    void setX(int x);
    void setY(int y);
    void setPos(QPoint point);
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;

    virtual QPoint getInputPortCenter() = 0;
    virtual QPoint getOutputPortCenter() = 0;

    void setName(QString name);
    const QString& getName() const; // Same as file name for user blocks

    // Attempt to load source content
    //bool loadSource();
    // After successfully loading the source, put it into a QTextEdit
    //QPlainTextEdit* getSource();

    int tabIndex; // Current tab index, -1 if not in tab

    /*
     *  Loads the widget that is shown in a new tab after double clicking the block
     *  This can either be a text editor with the source code (user block)
     *  or a graph showing the linear regression function etc
     */
    virtual QWidget* loadTabWidget() = 0;

private:
    int x, y, w, h;
    QString name;
};

typedef std::shared_ptr<Block> BlockPointer;

} } // graph, je

#endif // BLOCK_H
