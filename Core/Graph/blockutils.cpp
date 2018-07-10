#include "blockutils.h"

#include "blockloader.h"

namespace je { namespace graph {

// Factory function for generating new blocks. This must include all the possible blocks
std::map<block_types, std::function<std::shared_ptr<IBlock>()>> block_factory {
    {block_types::BLOCK, [](){ return std::make_shared<MyCustomBlock<int>>(); }}
};

} } // graph, je
