#include "blockutils.h"

#include "blockloader.h"

namespace je { namespace graph {

// Factory function for generating new blocks. This must include all the possible blocks
std::map<block_types, std::function<std::shared_ptr<IBlock>()>> block_factory {
    {B_MYCUSTOMBLOCK, [](){ return std::make_shared<MyCustomBlock<double>>(); }},
    {B_MYCUSTOMSOURCE, [](){ return std::make_shared<MyCustomSource<double>>(); }},
    {B_MYCUSTOMSINK, [](){ return std::make_shared<MyCustomSink<double>>(); }},
    {B_LINEARREGRESSIONBLOCK, [](){ return std::make_shared<LinearRegressionBlock<double>>(); }}
};

} } // graph, je
