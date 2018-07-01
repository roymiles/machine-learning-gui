#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <QDebug>
#include <memory>
#include <utility> // std::pair

#include "../Utility/utilities.h"
#include "port.h"
#include "../IO/blocksourcecodemanager.h"
#include "../Utility/utilities.h"
#include "iblock.h"
#include "blockutils.h"

namespace je { namespace graph {

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
template<typename block_type,
         typename in_type,
         typename out_type,
         typename tab_type>
class Block : public IBlock
{
public:
    Block() : IBlock(block_type::has_input, block_type::has_output) {}
    ~Block() {}

    // Overridden members call upon the templated utility functions declared above
    void draw(QPainter *painter) override
    {
        // Drawing a block is only dependant on the block type
        block_type_impl<block_type>::draw<in_type, out_type>(painter, this);
    }

    clickType mousePressEvent(QPoint &point) override
    {
        // The mouse press event check searches through all its ports and
        // therefore is block type dependant
        return block_type_impl<block_type>::mousePressEvent(point, this);
    }

    QWidget* tabWidget() override
    {
        // The widget that is returned is dependant on the tab type only
        return tab_type_impl<tab_type>::tabWidget(this);
    }

    // User may optionally ovveride this function
    virtual void init() override {}

    virtual out_type run(in_type in) = 0;
    void* run(void* in) override
    {
        out_type out = run(*((in_type *)in)); // Cast the input argument and call the users function
        out_type* retval = (out_type*)malloc(sizeof(out_type)); // Dynamically allocate memory for output (because returning a pointer)
        *retval = out;
        return retval;
    }
};


// block_type, in_type, out_type, tab_type
// Some common block types
typedef Block<sink_t, int, int, editable_t> isink_t;
typedef Block<source_t, int, int, editable_t> isource_t;
typedef Block<block_t, int, int, editable_t> iblock_t;

// For testing...
typedef Block<block_t, int, double, editable_t> test_t;

} } // je

#endif // BLOCK_H
