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
#include "../Components/IO/texteditor.h"
#include "../Utility/utilities.h"
#include "iblock.h"
#include "blockutils.h"
#include "blockbase.h"

namespace je { namespace graph {

/*
 *  All blocks inherit a specialised version of this class
 *  NOTE: The class is named Block to avoid collision with Block typedef (see bottom)
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
class Block : public BlockBase<block_type, in_type, out_type, tab_type>
{
public:
    Block() : BlockBase() {}
    ~Block() {}

    virtual void init() override {}    
    boost::any run_v(boost::any in) override {}
};

/*
 * BLOCK specialization
 */
template<typename in_type,
         typename out_type,
         typename tab_type>
class Block<block_t, in_type, out_type, tab_type> : public BlockBase<block_t, in_type, out_type, tab_type>
{
public:
    Block() : BlockBase() {}
    ~Block() {}

    // User may optionally ovveride this function
    virtual void init() override {}

    virtual out_type run(in_type in) = 0; // Block

    boost::any run_v(boost::any in) override
    {
        if(!utility::is_same<in_type, boost::blank>::value && !utility::is_same<out_type, boost::blank>::value) {
            // Cast the input argument and call the users function
            in_type in_cast = boost::any_cast<in_type>(in);
            out_type out = run(in_cast);

            // Save input/output
            prev_in = in_cast;
            prev_out = out;

            boost::any retval = out;
            return retval;
        } else {
            qFatal("Invalid template parameters in run_v()");
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
class Block<source_t, in_type, out_type, tab_type> : public BlockBase<source_t, in_type, out_type, tab_type>
{
public:
    Block() : BlockBase() {}
    ~Block() {}

    // User may optionally override this function
    virtual void init() override {}

    virtual out_type run(boost::blank in) = 0; // Source

    boost::any run_v(boost::any in) override
    {
        if(utility::is_same<in_type, boost::blank>::value) {
            // No input, therefore a source
            boost::blank b; // Empty input
            out_type out = run(b);
            prev_out = out; // Save output
            boost::any retval = out;
            return retval;
        } else {
            qFatal("Invalid template parameters in run_v()");
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
class Block<sink_t, in_type, out_type, tab_type> : public BlockBase<sink_t, in_type, out_type, tab_type>
{
public:
    Block() : BlockBase() {}
    ~Block() {}

    // User may optionally override this function
    virtual void init() override {}

    virtual boost::blank run(in_type in) = 0; // Source

    boost::any run_v(boost::any in) override
    {
        if(utility::is_same<out_type, boost::blank>::value) {
            // No output, therefore a sink
            in_type in_cast = boost::any_cast<in_type>(in);
            prev_in = in_cast; // Save input
            run(in_cast);
        } else {
            qFatal("Invalid template parameters in run_v()");
        }

        return nullptr; // Sinks never return anything
    }
};

// template parameters : block_type, in_type, out_type, tab_type
// Some common block types

template <typename T>
using Sink = Block<sink_t, T, boost::blank, editable_t>; // An input but no output (boost::blank)

template <typename T>
using Source = Block<source_t, boost::blank, T, editable_t>; // An output but no input

template<typename T>
using Block1 = Block<block_t, T, T, editable_t>;

template<typename T>
using GraphBlock = Block<block_t, T, T, graph_t>;

using Blank = Block<blank_t, boost::blank, boost::blank, editable_t>; // init will still be called for this type but run() won't be

// For testing...
typedef Block<block_t, int, double, editable_t> test_t;

} } // je

#endif // BLOCK_H
