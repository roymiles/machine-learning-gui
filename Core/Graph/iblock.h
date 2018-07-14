#pragma once

#include <utility> // std::pair
#include <QPoint>
#include <QString>
#include "port.h"
#include <chrono>
#include "../Utility/utilities.h"
#include <boost/any.hpp>

namespace je { namespace graph {

// Checks where a click takes place
enum click_types
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
    virtual click_types mousePressEvent(QPoint &point) = 0;
    virtual QWidget* tabWidget() = 0;

    /*
     * Get the in and out data types
     * This is so that the connection between two IBlocks can be verified
     * (based on matching data types)
     * NOTE: Must return a const type as the value is evaluated at compile time
     */
    virtual const utility::data_types getInType() = 0;
    virtual const utility::data_types getOutType() = 0;

    /*
     * This is called before the flow graph is run
     * This involve (for example) loading state information from a file
     */
    virtual void init() = 0;

    /*
     * The templated Block class will cast the boost::any to the appropriate types
     * and then call the user made run functions
     */
    virtual boost::any run_v(boost::any in) = 0;

    /*
     * The previous execution times of the current block are recorded
     * This is so that the user can easily identify bottlekneck in the design
     */
    void setExecutionTime(std::chrono::duration<double> time);
    std::chrono::duration<double> getExecutionTime();

    bool is_sink()
    {
        // A sink is defined as a block with an input and no output
        return (has_input && !has_output);
    }

    bool is_source()
    {
        // A source is defined as a block with an output but no input
        return (!has_input && has_output);
    }

    bool is_block()
    {
        return (has_input && has_output);
    }

    template<typename T>
    void addComponent(std::shared_ptr<T> component)
    {
        components.push_back(component);
    }

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        // Go through all the components and check if the component types are equal
        for(auto &c : components)
        {
            if(c.type() == typeid(std::shared_ptr<T>))
                return boost::any_cast<std::shared_ptr<T>>(c);
        }

        return nullptr;
    }

private:
    int x, y, w, h;
    QString name;
    int tabIndex;

    const bool has_input, has_output;

    // First -> Input, Second -> Output
    std::pair<PortPointer, PortPointer> ports;

    // The elapsed time of the previous execution
    std::chrono::duration<double> previousExecutionTimes;

    /*
     * Vector of any type of class component.
     * As components are typically templated and don't show
     * any particular hierarchy, it does not make sense to have
     * an IComponent type.
     *
     * The type of the components are only called inside the Block
     * class implementation, of which the component cast is known at compile
     * time. So there are no issues with invalid casts.
     */
    std::vector<boost::any> components;
};

typedef std::shared_ptr<IBlock> BlockPointer;

} } // graph, je
