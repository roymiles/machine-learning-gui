#ifndef PLOT_H
#define PLOT_H

#include "qcustomplot-source/qcustomplot.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <algorithm>
#include "linearregression.h"

namespace je {

using namespace boost::numeric::ublas;

template<typename T>
class Plot
{
public:
    Plot(QCustomPlot *customPlot)
    {
        this->customPlot = customPlot;
    }

    void scatterPlot(matrix<T> Y, matrix<T> X)
    {

    }

    void drawLine(T xStart, T xEnd, T xStep, calc_t<T> f)
    {
        assert(xStep > 0); // Ensures the loop ends and no division by zero

        const T len = std::abs(xEnd - xStart) / xStep;
        QVector<double> x(len), y(len);
        matrix<T> in(1, 2);
        for(size_t i = xStart; i < xEnd; i += xStep)
        {
          x[i] = i;
          in(0, 0) = 1;
          in(0, 1) = i;
          y[i] = f(in)(0,0);
        }

        customPlot->addGraph();
        customPlot->graph(0)->setData(x, y);
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
