#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "utilities.h"

using namespace boost::numeric::ublas;

namespace je{

// Find the linear relationship between an input vector and an output
// The feature size is p+1, and the # outputs = N
// This fixes the relationship to a linear model
template<typename T>
class LinearRegression
{
public:
    // [ROWS x COLUMNS] -> [size1 x size2]
    // Takes the output column vector [N x 1] and the input matrix [N x (p+1)] for training
    // The coefficients B will therefore be a [(p+1) x 1]
    LinearRegression(matrix<T> &Y, matrix<T> &X)
    {
        // e.g. for single output Y = [1 X1 X2 ... Xp][B0; B1; ... Bp]
        // Where p is the feature size, the X vector will be of length p+1
        // The input vector includes the scalar 1 in the first element to encapsulate the y-intercept
        // B is the column vector of coefficients, where B0 is the y-intercept

        assert(Y.size2() == 1 && Y.size1() == X.size1());
        const size_t N = Y.size1();   // # Outputs
        const size_t p = X.size2()-1; // Feature size

        // Estimate the vector of coefficients using least squares
        B.resize(p+1, 1);

        // The following can be derived from differentiating the RSS and setting equal to 0
        // B = (X^T * X)^-1 * X^T * y
        matrix<T> out;
        matrix<T> tmp = prod(trans(X), X);
        invertMatrix(tmp, out); // (X^T * X) will always be singular

        // NOTE: Nested prod is not allowed
        tmp = prod(out, trans(X));
        B = prod(tmp, Y); // This is a unique solution

        std::cout << "B = " << B << std::endl;
    }

    /*
     * Calculate Y based on the learnt coefficients
     */
    inline matrix<T> calculate(const matrix<T> &X) const
    {
        // Verify X dimensions, should be a single p+1 row vector
        assert(X.size1() == 1 && X.size2() == B.size1());

        // y = XB
        return prod(X, B);
    }

    matrix<T> operator()(const matrix<T> &X) const
    {
        return this->calculate(X);
    }

private:
    matrix<T> B;
};

} // je

#endif // LINEARREGRESSION_H
