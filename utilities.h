#pragma once

#include <QRect>
#include <QPoint>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace je {

using namespace boost::numeric::ublas;

template<typename T>
inline bool insideRect(T &rect, QPoint &point)
{
    return
    point.x() > rect->getX() &&  // Point is on right hand side of leftmost rectangle edge
    point.y() > rect->getY() &&  // Point is below the topmost rectangle edge
    point.x() < rect->getX() + rect->getW() &&  // Point is on the left of the rightmost rectangle edge
    point.y() < rect->getY() + rect->getH();    // Point is above the bottommost rectangle edge
}

/*
 * Matrix inversion routine.
 * Uses lu_factorize and lu_substitute in uBLAS to invert a matrix
 */
template<class T>
inline bool invertMatrix (const matrix<T>& input, matrix<T>& inverse)
{
   typedef permutation_matrix<std::size_t> pmatrix;
   // Create a working copy of the input
   matrix<T> A(input);
   // Create a permutation matrix for the LU-factorization
   pmatrix pm(A.size1());

   // Perform LU-factorization
   int res = lu_factorize(A,pm);
       if( res != 0 ) return false;

   // Create identity matrix of "inverse"
   //auto I = identity_matrix<T>(A.size1());
   //inverse.assign(I);
   inverse = identity_matrix<T>(A.size1());
   std::cout << "Identity = " << inverse << std::endl;

   // Backsubstitute to get the inverse
   lu_substitute(A, pm, inverse);

   return true;
}

bool testInvertMatrix();

// Pretty print a boost matrix
template<typename T>
void [[ deprecated ]] printMat(const matrix<T>& mat)
{
    std::cout << "{";
    // Loop through all rows
    for(size_t y = 0; y < mat.size1(); y++) // Not range based to help with accessing last iteration
    {
        // Loop through all columns (elements)
        bool first = true;
        for(size_t x = 0; x < mat.size2(); x++)
        {
            if(!first) std::cout << ", ";
            std::cout << mat(y, x);
            first = false;
        }

        if(y != mat.size1()-1)
            std::cout << "\n";
    }
    std::cout << "}" << std::endl;
}

} // je
