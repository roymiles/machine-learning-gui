#ifndef PLOT_H
#define PLOT_H

#include <boost/numeric/ublas/matrix.hpp>
#include <algorithm>
#include "linearregression.h"
#include <QVector>
#include <qcustomplot-source/qcustomplot.h>

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
    Plot(QCustomPlot *customPlot)
    {
        this->customPlot = customPlot;
    }

    // Used for plotting the original (training) data
    void scatterPlot(matrix<T> &Y, matrix<T> &X, int xcol = 1)
    {
        // Plot the Y column vector against a column in the input matrix (indexed by xcol)
        // Y is an Nx1 column vector
        // X is an Nx(p+1) matrix
        assert(Y.size1() == X.size1() && Y.size2() == 1);

        const size_t N = Y.size1();
        QVector<double> x(N), y(N);
        for(size_t i = 0; i < N; i++)
        {
          x[i] = X(i, xcol);
          y[i] = Y(i, 0);
        }

        customPlot->addGraph();
        customPlot->graph(0)->setData(x, y);
        // Give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        customPlot->graph(0)->setPen(QColor(50, 50, 50, 255));
        customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
        customPlot->graph(0)->setName("Training data");

        // Set axes ranges, so we see all data:
        T min = *std::min_element(x.constBegin(), x.constEnd());
        T max = *std::max_element(x.constBegin(), x.constEnd());
        customPlot->xAxis->setRange(min, max);

        min = *std::min_element(y.constBegin(), y.constEnd());
        max = *std::max_element(y.constBegin(), y.constEnd());
        customPlot->yAxis->setRange(min, max);
        customPlot->replot();
    }

    // Once the function f is estimated, can then draw this over the data
    void drawLine(T xStart, T xEnd, T xStep, calc_t<T> f)
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
          y[i] = f(in)(0,0);
        }

        customPlot->addGraph();
        customPlot->graph(1)->setData(x, y);
        customPlot->graph(1)->setPen(QPen(Qt::red));

        // Give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        // Set axes ranges, so we see all data:
        customPlot->xAxis->setRange(xStart, xEnd);

        T min = *std::min_element(y.constBegin(), y.constEnd());
        T max = *std::max_element(y.constBegin(), y.constEnd());
        customPlot->yAxis->setRange(min, max);
        customPlot->replot();
    }
private:
    QCustomPlot *customPlot;
};

} // je

#endif // PLOT_H
