#ifndef MYCUSTOMSINK_H
#define MYCUSTOMSINK_H

#include "../block.h"

using namespace je::graph;

class MyCustomSink : public Sink<int>
{
public:
    MyCustomSink();

    void init() override;
    void run(int in) override;
};

#endif // MYCUSTOMSINK_H
