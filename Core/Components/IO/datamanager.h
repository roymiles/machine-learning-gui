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

namespace je { namespace component { namespace io {

using namespace boost::numeric::ublas;

/*
 * List all the data sources that the DataManager supports
 * The class will have a specialized load function for each data source
 *
 * NOTE: NOTE USED AT THE MOMENT, JUST AN IDEA
 */
enum DataSources {
    D_GOVUK = 1 // www.example.com
};


// Handles the loading of data to and from .txt/.csv formats and boost::ublas::matrix
template<typename T>
class DataManager
{
public:
    DataManager() {}

    void getLabels(matrix<T> &mat) { mat = labels; } // Y
    void getData(matrix<T> &mat) { mat = data; } // X

    matrix<T> getLabels() { return labels; }
    matrix<T> getData() { return data; }

    // This should be templated for the source
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

            // Here Y ~= 3x + 100
            labels(i, 0) = 3*data(i, 1) + 100 + var_nor(); // Y = BX + D + e, where e ~ N(0, var) and D is a constant
        }

        return true; // Would return false is failed to load source
    }

private:
    int N; // Number of data points
    int p; // Data dimensionality (number of columns)

    matrix<T> data;   // X
    matrix<T> labels; // Y
    std::vector<std::string> columnNames;
};

} } } // io, component, je
