#pragma once

#include "../block.h"
#include "../../Components/Maths/Linear/regression.h"
#include "../../Components/IO/datamanager.h"

using namespace je;
using namespace boost::numeric::ublas;
using namespace je::component;

template<typename T>
class LinearRegressionBlock : public graph::GraphBlock<T> // In-type must be the same as out-type
{
public:
    LinearRegressionBlock() : graph::GraphBlock<T>()
    {
        // Initialise all the components
        auto r = std::make_shared<maths::linear::Regression<T>>();
        auto d = std::make_shared<io::DataManager<T>>();

        // Load the data and then perform regression
        d->load("example.dat");
        r->train(d->getLabels(), d->getData()); // Y, X

        // Add the components to the block
        addComponent(r);
        addComponent(d);
    }
    ~LinearRegressionBlock() {}

    void init() override
    {
        //qDebug() << "Initializing LinearRegressionBlock";
    }

    T run(T in) override
    {
        //qDebug() << "Running LinearRegressionBlock";

        // Calculate takes in a matrix of inputs.
        // In this case (feature size of 1) the mat will be a 1x1
        matrix<T> mat_in(1, 2);
        mat_in(0, 0) = 1; // See theory, this is for the y-intercept
        mat_in(0, 1) = in;

        //matrix<T> mat_out = regression.calculate(mat_in);
        matrix<T> mat_out = getComponent<maths::linear::Regression<T>>()->calculate(mat_in); //regression.calculate(mat_in);

        return mat_out(0, 0);
    }

private:
    //io::DataManager<T, io::GOVUK> dataManager;
    //maths::linear::Regression<T> regression;
};
