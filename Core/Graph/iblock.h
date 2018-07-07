#ifndef IBLOCK_H
#define IBLOCK_H

#include <utility> // std::pair
#include <QPoint>
#include <QString>
#include "port.h"
#include <chrono>

namespace je { namespace graph {

// Checks where a click takes place
enum click_types
{
    inPort,
    outPort,
    block,
    none
};

// All the supported template parameter types
enum data_types : int // Must explicitely specify the integral type to allow in class initialization
{
    INT,
    DOUBLE,
    _VOID // For source/sinks (underscore to avoid naming collision with void)
};

template<typename T>
struct type2enum
{
    static const data_types value = _VOID;
};

template<>
struct type2enum<int>
{
    static const data_types value = INT;
};

template<>
struct type2enum<double>
{
    static const data_types value = DOUBLE;
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
    virtual click_types mousePressEvent(QPoint &point) = 0;
    virtual QWidget* tabWidget() = 0;

    /*
     * Get the in and out data types
     * This is so that the connection between two IBlocks can be verified
     * (based on matching data types)
     */
    virtual data_types getInType() = 0;
    virtual data_types getOutType() = 0;

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
    virtual void* _run(void* in) = 0;

    /*
     * The previous execution times of the current block are recorded
     * This is so that the user can easily identify bottlekneck in the design
     */
    void setExecutionTime(std::chrono::duration<double> time);
    std::chrono::duration<double> getExecutionTime();

private:
    int x, y, w, h;
    QString name;
    int tabIndex;

    // First -> Input, Second -> Output
    std::pair<PortPointer, PortPointer> ports;

    // The elapsed time of the previous execution
    std::chrono::duration<double> previousExecutionTimes;
};

typedef std::shared_ptr<IBlock> BlockPointer;

} } // graph, je

#endif // IBLOCK_H
