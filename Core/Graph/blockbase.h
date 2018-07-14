#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include "blockutils.h"
#include "iblock.h"

namespace je { namespace graph {

/*
 * BlockBase contains some function/member definitions that are common
 * for all Block specializations
 */
template<typename block_type,
         typename in_type,
         typename out_type,
         typename tab_type>
class BlockBase : public IBlock
{
public:
    BlockBase() : IBlock(block_type::has_input, block_type::has_output)
    {
        // Some type assertions
        if(is_sink() && utility::is_same<out_type, void>::value && !utility::is_same<in_type, void>::value) // Must have void output and non-void input
            assert("Invalid sink template parameters");

        if(is_source() && !utility::is_same<out_type, void>::value && utility::is_same<in_type, void>::value) // Must have void input and non-void output
            assert("Invalid source template parameters");

        if(is_block() && !utility::is_same<out_type, void>::value && !utility::is_same<in_type, void>::value) // Must have non-void input and output
            assert("Invalid block template parameters");
    }

    ~BlockBase() {}

    // Overridden members call upon the templated utility functions declared above
    void draw(QPainter *painter) override
    {
        // Drawing a block is only dependant on the block type
        block_type_impl<block_type>::draw<in_type, out_type>(painter, this);
    }

    block_part_e mousePressEvent(QPoint &point) override
    {
        // The mouse press event check searches through all its ports and
        // therefore is block type dependant
        return block_type_impl<block_type>::mousePressEvent(point, this);
    }

    void mouseHoverEvent(block_part_e part, QPoint &point) override
    {
        block_type_impl<block_type>::mouseHoverEvent<in_type, out_type>(part, point, prev_in, prev_out);
    }

    QWidget* tabWidget() override
    {
        // The widget that is returned is dependant on the tab type only
        return tab_type_impl<tab_type, in_type, out_type>::tabWidget(this);
    }

    const utility::data_type_e getInType() override
    {
        return utility::type_info<in_type>::enumvalue;
    }

    const utility::data_type_e getOutType() override
    {
        return utility::type_info<out_type>::enumvalue;
    }
};

} } // graph, je

#endif // BLOCKBASE_H
