#include "utilities.h"

namespace je {

bool testInvertMatrix()
{
    matrix<int> X(3, 3);
    // Row 1
    X(0, 0) = 1;
    X(0, 1) = 0;
    X(0, 2) = 0;
    // Row 2
    X(1, 0) = 2;
    X(1, 1) = 1;
    X(1, 2) = 0;
    // Row 3
    X(2, 0) = 0;
    X(2, 1) = 0;
    X(2, 2) = 1;
    std::cout << "Test(X) = " << X << std::endl;

    matrix<int> result;
    invertMatrix(X, result);

    // Inverse of identity matrix should be an identity matrix
    std::cout << "Test(result)" << result << std::endl;
    return true;
}

} // je
