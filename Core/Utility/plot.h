#ifndef PLOT_H
#define PLOT_H

#include <boost/numeric/ublas/matrix.hpp>
#include <algorithm>
#include "../Maths/Linear/regression.h"
#include <QVector>
#include <qcustomplot-source/qcustomplot.h>
#include <tuple>
#include "../qcplinearcolormap.h"

namespace je { namespace utility {

using namespace boost::numeric::ublas;
using namespace maths::linear;

/*
 * This class offers an interface between the boost numeric structures (matrices) and QCustomPlot
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
        this->count      = 0;
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
        assert(X.size2() > 1 && X.size2() > std::get<0>(xcols) && X.size2() > std::get<1>(xcols));

        const size_t N = X.size1();
        QVector<xType> x1(N), x2(N);
        for(size_t i = 0; i < N; i++)
        {
          x1[i] = X(i, std::get<0>(xcols));
          x2[i] = X(i, std::get<1>(xcols));
        }

        colourMap = QCPLinearColorMap; // My colour stops are defined as values 0.0 through 1.0.
        colourMap.addColorStop(0.0, Qt::red);
        colourMap.addColorStop(0.1, Qt::blue);
        colourMap.addColorStop(0.3, Qt::green);

        QPen pen;
        pen.setColor(colourMap.color(0.0, 100.0, xValue)); // Set colour range 0 to 100.0.

        customPlot->addGraph();
        customPlot->graph(count)->setData(x1, x2);
        // Give the axes some labels:
        customPlot->xAxis->setLabel("x1");
        customPlot->yAxis->setLabel("x2");
        customPlot->graph(count)->setPen(pen);
        customPlot->graph(count)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(count)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
        customPlot->graph(count)->setName("Training data");

        // Set axes ranges, so we see all data:
        T min = *std::min_element(x1.constBegin(), x1.constEnd());
        T max = *std::max_element(x1.constBegin(), x1.constEnd());
        customPlot->xAxis->setRange(min, max);

        min = *std::min_element(x2.constBegin(), x2.constEnd());
        max = *std::max_element(x2.constBegin(), x2.constEnd());
        customPlot->yAxis->setRange(min, max);
        customPlot->replot();
        count++;
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
        assert(Y.size1() == X.size1() && Y.size2() == 1);

        const size_t N = Y.size1();
        QVector<T> x(N), y(N);
        for(int i = 0; i < N; i++)
        {
            x[i] = X(i, xcol);
            y[i] = Y(i, 0);
        }

        /*
         * NOTE: Duplicate code in scatterPlotYX and drawFunction, can we do something about this?
         */
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

        const int N = std::abs(xEnd - xStart) / xStep;
        QVector<T> x(N), y(N);
        matrix<T> in(1, 2);
        for(int i = xStart; i < xEnd; i += xStep)
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

} } // utility, je

#endif // PLOT_H
