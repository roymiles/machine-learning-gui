#include "linearregressionblock.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <qcustomplot-source/qcustomplot.h>
#include "../../Utility/plot.h"

LinearRegressionBlock::LinearRegressionBlock() : Block<int>()
{

}

void LinearRegressionBlock::init()
{
    qDebug() << "Initializing LinearRegressionBlock";

    using namespace boost::numeric::ublas;
    using namespace je::maths;

    // Example with a feature size of 2 (= p)
    const int N = 100; // # Outputs
    const int P = 1; // Dimensions

    boost::mt19937 rng; // Not seeded
    boost::normal_distribution<> nd(0.0, 5.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor(rng, nd);

    matrix<double> X(N, P+1); // [N x (p+1)]
    matrix<double> Y(N, 1); // [N x 1]
    // Generate the data
    for(int i = 0; i < N; i++)
    {
        X(i, 0) = 1; // y-intercept
        X(i, 1) = i;

        Y(i, 0) = -X(i, 1) + var_nor(); // Y = BX + e, where e ~ N(0, var)
    }

    // Function approximation
    auto f = new linear::Regression<double>(Y, X);

    auto customPlot = new QCustomPlot();
    je::utility::Plot<double> p(customPlot);

    // Draw the input training data as a scatter pot
    p.scatterPlotYX(Y, X);

    // And overlay the linear model prediction
    using namespace std::placeholders;  // For e.g. _1
    linear::calc_t<double> fptr = std::bind(&linear::Regression<double>::calculate, f, _1);
    p.drawFunction(0, 100, 1, fptr);
}

int LinearRegressionBlock::run(int in)
{
    //qDebug() << "Running LinearRegressionBlock";
    return 5 * 5;
}
