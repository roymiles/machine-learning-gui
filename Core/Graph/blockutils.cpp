#include "blockutils.h"

#include "blockloader.h"

namespace je { namespace graph {

// Factory function for generating new blocks. This must include all the possible blocks
std::map<block_types, std::function<std::shared_ptr<IBlock>()>> block_factory {
    {block_types::MYCUSTOMBLOCK, [](){ return std::make_shared<MyCustomBlock<double>>(); }},
    {block_types::MYCUSTOMSOURCE, [](){ return std::make_shared<MyCustomSource<double>>(); }},
    {block_types::MYCUSTOMSINK, [](){ return std::make_shared<MyCustomSink<double>>(); }},
    {block_types::LINEARREGRESSIONBLOCK, [](){ return std::make_shared<LinearRegressionBlock<double>>(); }}
};

} } // graph, je
