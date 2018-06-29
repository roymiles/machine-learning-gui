#ifndef USERBLOCK_H
#define USERBLOCK_H

#include <vector>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <memory>
#include <utility> // std::pair
#include <boost/optional.hpp>

#include "../../Utility/utilities.h"
#include "../block.h"
#include "../port.h"
#include "../inputport.h"
#include "../outputport.h"
#include "../../IO/blocksourcecodemanager.h"
#include "../../Utility/utilities.h"

namespace je { // Not in graph sub namespace to reduce user boilerplate code

struct sink_t { enum { has_input = true, has_output = false }; };
struct source_t { enum { has_input = false, has_output = true }; };
struct block_t { enum { has_input = true, has_output = true }; };

struct editable_t { };
struct graph_t { };

/*
 *  All blocks inherit a specialised version of this class
 *  --- T PARAMS ---
 *  blockType   : Defines the connected ports. Either a source, sink, or generic block
 *  inType      : The type the block accepts
 *  outType     : The type the block returns
 *  tabType     : What happens when the user double clicks on the block.
 *                An editable block will open a text editor with the source code that defines
 *                the execution of the block
 */

using namespace je::graph;

template<typename blockType,
         typename inType,
         typename outType,
         typename tabType,
         typename derived>
class CustomBlockBase
{
public:
    CustomBlockBase();
    ~CustomBlockBase();

    /*
     * This base class defines all functionality that is common for all
     * CustomBlock template specialisations
     */

    std::pair<PortPointer, PortPointer> getPorts()
    {
        return ports;
    }

private:
    // First -> Input, Second -> Output
    std::pair<PortPointer, PortPointer> ports;
};

template<typename blockType,
         typename inType,
         typename outType,
         typename tabType>
class CustomBlock : public CustomBlockBase<blockType,
                                           inType,
                                           outType,
                                           tabType,
                                           CustomBlock<blockType, inType, outType, tabType>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

/*
 * Following specialisations for blockType
 */
template<typename inType,
         typename outType,
         typename tabType>
class CustomBlock<source_t, inType, outType, tabType> : public CustomBlockBase<source_t,
                                                                               inType,
                                                                               outType,
                                                                               tabType,
                                                                               CustomBlock<source_t, inType, outType, tabType>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

template<typename inType,
         typename outType,
         typename tabType>
class CustomBlock<sink_t, inType, outType, tabType> : public CustomBlockBase<sink_t,
                                                                             inType,
                                                                             outType,
                                                                             tabType,
                                                                             CustomBlock<sink_t, inType, outType, tabType>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

template<typename inType,
         typename outType,
         typename tabType>
class CustomBlock<block_t, inType, outType, tabType> : public CustomBlockBase<block_t,
                                                                              inType,
                                                                              outType,
                                                                              tabType,
                                                                              CustomBlock<block_t, inType, outType, tabType>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

/*
 * Following specialisations for tabType
 */
template<typename blockType,
         typename inType,
         typename outType>
class CustomBlock<blockType, inType, outType, editable_t> : public CustomBlockBase<blockType,
                                                                                   inType,
                                                                                   outType,
                                                                                   editable_t,
                                                                                   CustomBlock<blockType, inType, outType, editable_t>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

template<typename blockType,
         typename inType,
         typename outType>
class CustomBlock<blockType, inType, outType, graph_t> : public CustomBlockBase<blockType,
                                                                                inType,
                                                                                outType,
                                                                                graph_t,
                                                                                CustomBlock<blockType, inType, outType, graph_t>>
{
public:
    CustomBlock();
    ~CustomBlock();

    void draw(QPainter *painter);
    clickType mousePressEvent(QPoint &point);
    QWidget* loadTabWidget();
};

// Some common block types
typedef CustomBlock<sink_t, int, int, editable_t> isink_t;
typedef CustomBlock<source_t, int, int, editable_t> isource_t;
typedef CustomBlock<block_t, int, int, editable_t> iblock_t;


} // je

#endif // USERBLOCK_H
