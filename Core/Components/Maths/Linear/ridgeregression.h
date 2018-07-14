#pragma once

namespace je { namespace component { namespace maths { namespace linear {

/*
 * Ridge regression is similar to ordinary linear regression but shrinks the regression coefficients
 * This is due to an extra constraint on the size of the coefficients which is introduced to make the closed form expression
 * Large coefficients arise from high correllation between features, which can lead to large variance
 *
 * Ridge regression reduces this variance significantly at a trade-off for the bias
 */
class RidgeRegression
{
public:
    RidgeRegression();
};

} } } } // linear, maths, component, je
