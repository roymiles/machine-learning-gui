#pragma once

#include <memory>
#include "Utility/utilities.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "Utility/plot.h"

using namespace boost::numeric::ublas;

namespace je {

using namespace utility;

class IComponent
{

public:
    IComponent(component_types t) : component_type(t) {}

    component_types getComponentType()
    {
        return component_type;
    }

    // These are used in Regression class, for example.
    //virtual matrix<int> calculate(const matrix<int> &X) { matrix<int> out; return out; }
    //virtual matrix<double> calculate(const matrix<double> &X) { matrix<double> out; return out; }

    virtual void draw(utility::Plot<int> &p) {}
    virtual void draw(utility::Plot<double> &p) {}

private:
    component_types component_type;
};

typedef std::shared_ptr<IComponent> ComponentPointer;

}
