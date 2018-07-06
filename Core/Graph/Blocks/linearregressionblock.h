#pragma once

#include "../block.h"
#include "../../Maths/Linear/regression.h"

using namespace je::graph;

class LinearRegressionBlock : public Block<int>
{
public:
    LinearRegressionBlock();

    void init() override;
    int run(int in) override;
};
