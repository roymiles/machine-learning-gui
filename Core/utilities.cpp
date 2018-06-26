#include "utilities.h"

#include "linearregression.h"
#include "plot.h"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <qcustomplot-source/qcustomplot.h>

namespace je {

// TODO: Move tests into a seperate file

// Unit test for "invertMatrix" function
bool testInvertMatrix()
{
    matrix<int> X(3, 3);
    // Row 1
    X(0, 0) = 1;
    X(0, 1) = 0;
    X(0, 2) = 0;
    // Row 2
    X(1, 0) = 2;
    X(1, 1) = 1;
    X(1, 2) = 0;
    // Row 3
    X(2, 0) = 0;
    X(2, 1) = 0;
    X(2, 2) = 1;
    std::cout << "Test(X) = " << X << std::endl;

    matrix<int> result;
    invertMatrix(X, result);

    // Inverse of identity matrix should be an identity matrix
    std::cout << "Test(result)" << result << std::endl;
    return true;
}

// Create some dummy data, perform linear regression, and then add it to a tab
void testLinearRegression(QTabWidget *tabWidget)
{
    using namespace boost::numeric::ublas;

    // Example with a feature size of 1 (p = 1)
    const int N = 100; // # Outputs
    const int P = 1; // Dimensions

    boost::mt19937 rng; // Not seeded
    boost::normal_distribution<> nd(0.0, 5.0);
    boost::variate_generator<boost::mt19937&,
                             boost::normal_distribution<> > var_nor(rng, nd);

    matrix<double> X(N, P+1); // [N x (p+1)]
    matrix<double> Y(N, 1); // [N x 1]
    for(int i = 0; i < N; i++)
    {
        X(i, 0) = 1; // y-intercept
        X(i, 1) = i;
        Y(i, 0) = i + var_nor(); // Y = BX + e, where e ~ N(0, var)
    }

    // Function approximation
    auto f = new LinearRegression<double>(Y, X);

    auto customPlot = new QCustomPlot();
    Plot<double> p(customPlot);

    // Draw the input training data as a scatter pot
    p.scatterPlot(Y, X);

    // And overlay the linear model prediction
    using namespace std::placeholders;  // For e.g. _1
    calc_t<double> fptr = std::bind(&LinearRegression<double>::calculate, f, _1);
    p.drawLine(0, 100, 1, fptr);

    tabWidget->addTab(customPlot, "Linear regression test");
}

} // je