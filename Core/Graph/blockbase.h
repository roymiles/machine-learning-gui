#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include "blockutils.h"

namespace je { namespace graph {

/*
 * _BlockBase contains some function/member definitions that are common
 * for all _Block specializations
 */
template<typename block_type,
         typename in_type,
         typename out_type,
         typename tab_type>
class _BlockBase
{
public:
    _BlockBase()
    {
        // Some type assertions
        if(is_sink() && utility::is_same<out_type, void>::value && !utility::is_same<in_type, void>::value) // Must have void output and non-void input
            assert("Invalid sink template parameters");

        if(is_source() && !utility::is_same<out_type, void>::value && utility::is_same<in_type, void>::value) // Must have void input and non-void output
            assert("Invalid source template parameters");

        if(is_block() && !utility::is_same<out_type, void>::value && !utility::is_same<in_type, void>::value) // Must have non-void input and output
            assert("Invalid block template parameters");
    }

    ~_BlockBase() {}

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

    static bool is_block()
    {
        return (block_type::has_input && block_type::has_output);
    }
};

} } // graph, je

#endif // BLOCKBASE_H
