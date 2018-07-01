#ifndef IBLOCK_H
#define IBLOCK_H

#include <utility> // std::pair
#include <QPoint>
#include <QString>
#include "port.h"

namespace je { namespace graph {

// Checks where a click takes place
enum clickType
{
    inPort,
    outPort,
    block,
    none
};

class IBlock
{
public:
    IBlock() = delete;
    IBlock(bool has_input, bool has_output);
    ~IBlock();

    void setX(int x);
    void setY(int y);
    void setPos(QPoint &point);
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    void getRect(QRect &rect) const;
    std::pair<PortPointer, PortPointer> getPorts() const;
    void setName(QString name);
    const QString& getName() const;
    void setTabIndex(int tabIndex);
    int getTabIndex() const;

    // Virtual methods
    virtual void draw(QPainter *painter) = 0;
    virtual clickType mousePressEvent(QPoint &point) = 0;
    virtual QWidget* tabWidget() = 0;

    /*
     * This is called before the flow graph is run
     * This involve (for example) loading state information from a file
     * *Training* from a dataset
     */
    virtual void init() = 0;

    /*
     * The templated Block class will cast the void* to the appropriate types
     * and then call the user made run functions
     */
    virtual void* run(void* in) = 0;

private:
    int x, y, w, h;
    QString name;
    int tabIndex;

    // First -> Input, Second -> Output
    std::pair<PortPointer, PortPointer> ports;
};

typedef std::shared_ptr<IBlock> BlockPointer;

} } // graph, je

#endif // IBLOCK_H
