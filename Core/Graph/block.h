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
 *  NOTE: The class is named _Block to avoid collision with Block typedef (see bottom)
 *        This makes the user code more intuitive
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
class _Block : public IBlock
{
public:
    _Block() : IBlock(block_type::has_input, block_type::has_output) {}
    ~_Block() {}

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

    static bool is_sink()
    {
        // A sink is defined as a block with an input and no output
        return (block_type::has_input && !block_type::has_output);
    }

    static bool is_source()
    {
        // A source is defined as a block with an output but no input
        return (!block_type::has_input && block_type::has_output);
    }
};

// This is needed because func(void in) is an illegal expression
// An alternative is class template specialisation, but this adds too much bulk code
struct void_t {};

// template parameters : block_type, in_type, out_type, tab_type
// Some common block types

template <typename T>
using Sink = _Block<sink_t, T, void_t, editable_t>; // An input but no output (void_t)

template <typename T>
using Source = _Block<source_t, void_t, T, editable_t>; // An output but no input

template<typename T>
using Block = _Block<block_t, T, T, editable_t>;

using Blank = _Block<blank_t, void_t, void_t, editable_t>; // init will still be called for this type but run() won't be

// For testing...
typedef _Block<block_t, int, double, editable_t> test_t;

} } // je

#endif // BLOCK_H
