#ifndef PLOT_H
#define PLOT_H

#include <boost/numeric/ublas/matrix.hpp>
#include <algorithm>
#include "linearregression.h"
#include <QVector>
#include <qcustomplot-source/qcustomplot.h>
#include <tuple>

namespace je {

using namespace boost::numeric::ublas;

/*
 * This class offers an interface between the boost numeric structures and QCustomPlot
 * It can take Boost::Matrix data and plot them on a QCustomPlot instance
 */
template<typename T>
class Plot
{
public:
    /*
     * Class takes in an instance of QCustomPlot. All the graph drawing will be
     * done using this object. See QCustomPlot documentation online
     */
    Plot() = delete;
    Plot(QCustomPlot *customPlot)
    {
        this->customPlot = customPlot;
        this->count      = count;
    }

    /*
     * Plot two inputs (features) against each other on axis
     * The colour of the point is determined by Y
     * --- PARAMS ---
     * xcols : The columns in the input matrix X used for plotting
     * Y     : The output matrix can either be continuous or discrete.
     *         In the discrete case, each distinct value will have a unique point colour
     *         In the continuous case, the values will not be colour coded
     */
    void scatterPlotXX(matrix<T> &X, matrix<T> &Y, std::tuple<int, int> xcols)
    {
        // Y is an Nx1 column vector
        // X is an Nx(p+1) matrix

        // X must have at least 2 inputs and xcols must exist in X
        assert(X.size2() > 1 && X.size2() > std::get<0>(xcols) && X.size2() > std::get<1>(result));
    }

    /*
     * Used for plotting the original (training) data
     * The output value (y-axis) will be plotted against a single input value (x-axis)
     * The choice of input value, as the function may be multivariate, is specified by xcol
     */
    void scatterPlotYX(matrix<T> &Y, matrix<T> &X, int xcol = 1)
    {
        // Plot the Y column vector against a column in the input matrix (indexed by xcol)
        // Y is an Nx1 column vector
        // X is an Nx(p+1) matrix
        std::cout << Y << X << std::endl;
        assert(Y.size1() == X.size1() && Y.size2() == 1);

        const size_t N = Y.size1();
        QVector<double> x(N), y(N);
        for(size_t i = 0; i < N; i++)
        {
          x[i] = X(i, xcol);
          y[i] = Y(i, 0);
        }

        customPlot->addGraph();
        customPlot->graph(count)->setData(x, y);
        // Give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        customPlot->graph(count)->setPen(QColor(50, 50, 50, 255));
        customPlot->graph(count)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(count)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
        customPlot->graph(count)->setName("Training data");

        // Set axes ranges, so we see all data:
        T min = *std::min_element(x.constBegin(), x.constEnd());
        T max = *std::max_element(x.constBegin(), x.constEnd());
        customPlot->xAxis->setRange(min, max);

        min = *std::min_element(y.constBegin(), y.constEnd());
        max = *std::max_element(y.constBegin(), y.constEnd());
        customPlot->yAxis->setRange(min, max);
        customPlot->replot();
        count++;
    }

    /*
     * Once the function f is estimated, can then draw this over the data
     * This function will iterate through the supplied range (x) and calculate
     * the output y = f(x). This will be plotted
     * --- PARAMS ---
     * f    : A function pointer to calculate the output value
     */
    void drawFunction(T xStart, T xEnd, T xStep, calc_t<T> f)
    {
        assert(xStep > 0); // Ensures the loop ends and no division by zero

        const size_t N = std::abs(xEnd - xStart) / xStep;
        QVector<double> x(N), y(N);
        matrix<T> in(1, 2);
        for(size_t i = xStart; i < xEnd; i += xStep)
        {
          x[i] = i;
          in(0, 0) = 1; // See theory, this is for the y-intercept
          in(0, 1) = i;
          y[i] = f(in)(0,0); // calc<T> returns a single element matrix<T>
        }

        customPlot->addGraph();
        customPlot->graph(count)->setData(x, y);
        customPlot->graph(count)->setPen(QPen(Qt::red));

        // Give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        // Set axes ranges, so we see all data:
        customPlot->xAxis->setRange(xStart, xEnd);

        T min = *std::min_element(y.constBegin(), y.constEnd());
        T max = *std::max_element(y.constBegin(), y.constEnd());
        customPlot->yAxis->setRange(min, max);
        customPlot->replot();
        count++;
    }
private:
    QCustomPlot *customPlot;

    int count; // Keeps track of the number of graphs to enable multiple plot calls ->graph(count)
};

} // je

#endif // PLOT_H
