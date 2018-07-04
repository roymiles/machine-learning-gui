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
#include "blockbase.h"

namespace je { namespace graph {

// This is needed because func(void in) is an illegal expression
// An alternative is class template specialisation, but this adds too much bulk code (had to be done though)
// NOTE: No longer used, makes user code ugly
//struct void_t {};

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
class _Block : public IBlock, public _BlockBase<block_type, in_type, out_type, tab_type>
{
public:
    _Block() : IBlock(block_type::has_input, block_type::has_output), _BlockBase() {}
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

    virtual void init() override {}    
    void* _run(void* in) override {}
};

/*
 * BLOCK specialization
 */
template<typename in_type,
         typename out_type,
         typename tab_type>
class _Block<block_t, in_type, out_type, tab_type> : public IBlock, public _BlockBase<block_t, in_type, out_type, tab_type>
{
public:
    _Block() : IBlock(block_t::has_input, block_t::has_output), _BlockBase() {}
    ~_Block() {}

    void draw(QPainter *painter) override
    {
        block_type_impl<block_t>::draw<in_type, out_type>(painter, this);
    }

    clickType mousePressEvent(QPoint &point) override
    {
        return block_type_impl<block_t>::mousePressEvent(point, this);
    }

    QWidget* tabWidget() override
    {
        return tab_type_impl<tab_type>::tabWidget(this);
    }

    // User may optionally ovveride this function
    virtual void init() override {}

    virtual out_type run(in_type in) = 0; // Block

    void* _run(void* in) override
    {
        if(!is_same<in_type, void>::value && !is_same<out_type, void>::value) {
            // Cast the input argument and call the users function
            out_type out = run(*((in_type *)in));
            qDebug() << "Block out = " << out;
            // Dynamically allocate memory for output (because returning a pointer)
            out_type* retval = (out_type*)malloc(sizeof(out_type));
            *retval = out;
            return retval;
        } else {
            assert("Invalid template parameters in _run()");
            return nullptr;
        }
    }
};

/*
 * SOURCE specialization
 */
template<typename in_type,
         typename out_type,
         typename tab_type>
class _Block<source_t, in_type, out_type, tab_type> : public IBlock, public _BlockBase<source_t, in_type, out_type, tab_type>
{
public:
    _Block() : IBlock(source_t::has_input, source_t::has_output), _BlockBase() {}
    ~_Block() {}

    void draw(QPainter *painter) override
    {
        block_type_impl<source_t>::draw<in_type, out_type>(painter, this);
    }

    clickType mousePressEvent(QPoint &point) override
    {
        return block_type_impl<source_t>::mousePressEvent(point, this);
    }

    QWidget* tabWidget() override
    {
        return tab_type_impl<tab_type>::tabWidget(this);
    }

    // User may optionally override this function
    virtual void init() override {}

    virtual out_type run() = 0; // Source

    void* _run(void* in) override
    {
        if(is_same<in_type, void>::value) {
            // No input, therefore a source
            out_type out = run();
            qDebug() << "Source out = " << out;
            out_type* retval = (out_type*)malloc(sizeof(out_type));
            *retval = out;
            return retval;
        } else {
            assert("Invalid template parameters in _run()");
            return nullptr;
        }
    }
};

/*
 * SINK specialization
 */
template<typename in_type,
         typename out_type,
         typename tab_type>
class _Block<sink_t, in_type, out_type, tab_type> : public IBlock, public _BlockBase<sink_t, in_type, out_type, tab_type>
{
public:
    _Block() : IBlock(sink_t::has_input, sink_t::has_output), _BlockBase() {}
    ~_Block() {}

    void draw(QPainter *painter) override
    {
        block_type_impl<sink_t>::draw<in_type, out_type>(painter, this);
    }

    clickType mousePressEvent(QPoint &point) override
    {
        return block_type_impl<sink_t>::mousePressEvent(point, this);
    }

    QWidget* tabWidget() override
    {
        return tab_type_impl<tab_type>::tabWidget(this);
    }

    // User may optionally override this function
    virtual void init() override {}

    virtual void run(in_type in) = 0; // Source

    void* _run(void* in) override
    {
        if(is_same<out_type, void>::value) {
            // No output, therefore a sink
            run(*((in_type *)in));
        } else {
            assert("Invalid template parameters in _run()");
        }

        return nullptr;
    }
};

// template parameters : block_type, in_type, out_type, tab_type
// Some common block types

template <typename T>
using Sink = _Block<sink_t, T, void, editable_t>; // An input but no output (void_t)

template <typename T>
using Source = _Block<source_t, void, T, editable_t>; // An output but no input

template<typename T>
using Block = _Block<block_t, T, T, editable_t>;

using Blank = _Block<blank_t, void, void, editable_t>; // init will still be called for this type but run() won't be

// For testing...
typedef _Block<block_t, int, double, editable_t> test_t;

} } // je

#endif // BLOCK_H
