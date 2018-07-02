#ifndef MYCUSTOMSOURCE_H
#define MYCUSTOMSOURCE_H

#include "../block.h"

using namespace je::graph;

class MyCustomSource : public Source<int>
{
public:
    MyCustomSource();

    void init() override;
    int run(void_t in) override;
};

#endif // MYCUSTOMSOURCE_H
