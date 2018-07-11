#pragma once

#include <vector>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include "../icomponent.h"

namespace je { namespace component { namespace io {

using namespace boost::numeric::ublas;

/*
 * List all the data sources that the DataManager supports
 * The class will have a specialized load function for each source
 */
enum DataSources {
    D_GOVUK = 1 // www.example.com
};

template<typename T>
class DataManagerBase : public IComponent
{
public:
    DataManagerBase() : IComponent(C_DATA_MANAGER) {}

    static component_types componentType()
    {
        return C_DATA_MANAGER;
    }

    void getLabels(matrix<T> &mat) override { mat = labels; } // Y
    void getData(matrix<T> &mat) override { mat = data; } // X

    matrix<T> getLabels() { return labels; }
    matrix<T> getData() { return data; }

protected:
    int N; // Number of data points
    int p; // Data dimensionality (number of columns)

    matrix<T> data;   // X
    matrix<T> labels; // Y
    std::vector<std::string> columnNames;
};

/*
 * Handles the loading of data to and from .txt/.csv formats and boost::ublas::matrix
 */
template<typename T,     // Data type, e.g. int, double
         DataSources S>  // Data source e.g. GOVUK, EXAMPLECOM
class DataManager : public DataManagerBase<T>
{
public:
    DataManager() : DataManagerBase()
    {
        assert("Invalid type parameters"); // This class will be instatiated if all other class specializations fail
    }

    bool load(std::string path) { return false; }
};

// Class specializations (currently just testing)
template<>
class DataManager<double, D_GOVUK> : public DataManagerBase<double>
{
public:
    DataManager() : DataManagerBase()
    {
    }

    bool load(std::string path)
    {
        // Example with a feature size of 2 (= p)
        const int N = 100; // # Outputs
        const int P = 1; // Dimensions

        boost::mt19937 rng; // Not seeded
        boost::normal_distribution<> nd(0.0, 5.0);
        boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor(rng, nd);

        data.resize(N, P+1); // [N x (p+1)]
        labels.resize(N, 1); // [N x 1]
        // Generate the data
        for(int i = 0; i < N; i++)
        {
            data(i, 0) = 1; // y-intercept (NOTE: B will have 2 coefficients for a 1-1 mapping due to this offset)
            data(i, 1) = i;

            // Here Y ~= -7*X
            labels(i, 0) = -7*data(i, 1) + 10 + var_nor(); // Y = BX + D + e, where e ~ N(0, var) and D is a constant
        }

        return true; // Would return false is failed to load source
    }
};

} } } // io, component, je
