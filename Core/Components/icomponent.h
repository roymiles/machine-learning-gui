#pragma once

#include <memory>
#include "../Utility/utilities.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "plot.h"

using namespace boost::numeric::ublas;

namespace je { namespace component {

using namespace utility;

class IComponent
{

public:
    IComponent(component_types t) : component_type(t) {}

    component_types getComponentType()
    {
        return component_type;
    }

    /*
     * At the moment, this class has lots of optionally overridable functions
     * This is not an ideal design architecture but is sufficient for now
     */

    // Maths/Linear/Regression
    virtual matrix<int> calculate(const matrix<int> &X) { matrix<int> out; return out; }
    virtual matrix<double> calculate(const matrix<double> &X) { matrix<double> out; return out; }

    // Maths/Linear/Regression
    virtual void draw(Plot<int> &p) {}
    virtual void draw(Plot<double> &p) {}

    // NOTE: overriden functions must have different signatures (return type alone cant be the only different)
    // IO/DataManager
    virtual void getLabels(matrix<int> &mat) {}
    virtual void getLabels(matrix<double> &mat) {}
    virtual void getData(matrix<int> &mat) {}
    virtual void getData(matrix<double> &mat) {}

private:
    component_types component_type;
};

typedef std::shared_ptr<IComponent> ComponentPointer;

} } // component, je
