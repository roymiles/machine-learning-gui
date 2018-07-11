#ifndef UTILITIES_H
#define UTILITIES_H

#include <QRect>
#include <QPoint>
#include <QTabWidget>
#include <QColor>
#include <QMessageBox>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <string>
#include <fstream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace je { namespace utility {

using namespace boost::numeric::ublas;

/*
 * All the supported template parameter types
 * This is used to populate the dropdown list in addblockdialog
 */
enum data_types
{
    INT     = 0,
    DOUBLE  = 1,
    _VOID   = 2, // For source/sinks (underscore to avoid naming collision with void)
    _MAXD   = 3
};

/*
 *
 */
enum component_types
{
    REGRESSION_COMP = 0
};

/*
 * is_same<T,U>::value is true iff T == U
 */
template<typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template<typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

/*
 * Give generic type information for all the data_types (specified above)
 * Different input/output data types will have different coloured ports
 * Can also be used to convert back to enum data_type
 */
template<typename T>
struct type_info
{
    static QColor colour() { return Qt::gray; } // Default type colour
    static const data_types enumvalue = data_types::INT;
};

// Class specializations
template<>
struct type_info<int>
{
    static QColor colour() { return Qt::red; }
    static const data_types enumvalue = data_types::INT;
};

template<>
struct type_info<double>
{
    static QColor colour() { return Qt::green; }
    static const data_types enumvalue = data_types::DOUBLE;
};

/*
 * Give a generic GUI message pop-up box for the user
 */
void inputDialog(QString message);

/*
 * --- PARAMS ---
 * rect     : Arbitrary type that must specify getX, getY, getW, and getH
 */
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
template<typename T>
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
   inverse = identity_matrix<T>(A.size1());

   // Backsubstitute to get the inverse
   lu_substitute(A, pm, inverse);

   return true;
}

bool isValidBlockName(const QString fileName);

// The following should not be in utilities!!
bool testInvertMatrix();
void testLinearRegression(QTabWidget *tabWidget);

} } // utility, je

#endif
