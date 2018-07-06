#pragma once

#include <vector>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace je { namespace io {

using namespace boost::numeric::ublas;

enum DataSources {
    GOVUK = 1
};

template<typename T, int N, int p>
class DataManagerBase
{
    DataManagerBase()
    {
        columnNames.reserve(p);
        data.resize(p, N); // [p x N]
        labels.resize(1, N);
    }

    matrix<T> data;
    matrix<T> labels;
    std::vector<std::string> columnNames;
};

/*
 * Handles the loading of data to and from .txt/.csv formats and boost::ublas::matrix
 */
template<typename T, // Data type
         int N,      // # Data points
         int p,      // Dimensionality
         DataSources S>  // Data source
class DataManager : public DataManagerBase<T, N, p>
{
public:
    DataManager() : DataManagerBase()
    {
        assert("Invalid type parameters"); // This class will be instatiated if all other class specializations fail
    }
};

// Class specializations
template<typename T, // Data type
         int N,      // # Data points
         int p>      // Dimensionality
class DataManager<T, N, p, GOVUK> : public DataManagerBase<T, N, p>
{
public:
    DataManager() : DataManagerBase()
    {
    }
};

} } // io, je
