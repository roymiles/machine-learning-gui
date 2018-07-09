#pragma once

#include "../block.h"
#include "../../Maths/Linear/regression.h"
#include "../../IO/datamanager.h"

using namespace je;
using namespace boost::numeric::ublas;

template<typename T>
class LinearRegressionBlock : public graph::GraphBlock<T> // In-type must be the same as out-type
{
public:
    LinearRegressionBlock() : graph::GraphBlock<T>() {}
    ~LinearRegressionBlock() {}

    void init() override
    {
        //qDebug() << "Initializing LinearRegressionBlock";

        dataManager.load("example.dat"); // Load the data
        regression.train(dataManager.labels, dataManager.data); // Y, X
    }

    T run(T in) override
    {
        //qDebug() << "Running LinearRegressionBlock";

        // Calculate takes in a matrix of inputs.
        // In this case (feature size of 1) the mat will be a 1x1
        matrix<T> mat_in(1, 2);
        mat_in(0, 0) = 1; // See theory, this is for the y-intercept
        mat_in(0, 1) = in;

        matrix<T> mat_out = regression.calculate(mat_in);

        return mat_out(0, 0);
    }

private:
    io::DataManager<T, io::GOVUK> dataManager;
    maths::linear::Regression<T> regression;
};
