#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Graph/userblock.h"

using namespace boost::numeric::ublas;

namespace je{

// Find the linear relationship between an input vector and an output
// The feature size is p+1, and the # outputs = N
// This fixes the relationship to a linear model
// TODO: Allow multi-output data
template<typename T>
class LinearRegression : public UserBlock
{
public:

    /*
     * Must specify the X, Y data
     */
    LinearRegression() = delete;
    LinearRegression(matrix<T> &Y, matrix<T> &X) : UserBlock()
    {
        train(Y, X);
    }

    /*
     * Calculate Y based on the learnt coefficients
     */
    matrix<T> calculate(const matrix<T> &X)
    {
        // Verify X dimensions, should be a single p+1 row vector
        assert(X.size1() == 1 && X.size2() == B.size1());

        // y = XB (X includes a column of all 1s to encapsulate the y-intercept)
        return prod(X, B);
    }

    // TODO: Get this working, would be a lot easier to just call f(x), where f is an instance of this class
    matrix<T> operator()(const matrix<T> &X)
    {
        return this->calculate(X);
    }

private:

    // [ROWS x COLUMNS] -> [size1 x size2]
    // Takes the output column vector [N x 1] and the input matrix [N x (p+1)] for training
    // The coefficients B will therefore be a [(p+1) x 1]
    void train(matrix<T> &Y, matrix<T> &X)
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
    }


    matrix<T> B; // Regression coefficients
};

template<typename T>
using calc_t = std::function<matrix<T>(matrix<T> const&)>;

} // je

#endif // LINEARREGRESSION_H
