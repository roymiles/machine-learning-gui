#include "utilities.h"

#include "qcustomplot-source/qcustomplot.h"
#include "linearregression.h"
#include "plot.h"

namespace je {

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
    // y = 5x -> B = 5
    const int N = 3; // # Outputs
    const int P = 1; // Dimensions

    matrix<double> X(N, P+1); // [N x (p+1)] -> [3 x 2]
    // Row 1
    X(0, 0) = 1;
    X(0, 1) = 1;
    // Row 2
    X(1, 0) = 1;
    X(1, 1) = 2;
    // Row 3
    X(2, 0) = 1;
    X(2, 1) = 3;

    matrix<double> Y(N, 1); // # outputs = 3 -> [3 x 1]
    Y(0, 0) = 100;
    Y(1, 0) = 200;
    Y(2, 0) = 300;

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
