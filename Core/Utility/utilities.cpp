#include "utilities.h"

#include "../Components/Maths/Linear/regression.h"
#include "../Components/plot.h"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <qcustomplot-source/qcustomplot.h>

namespace je { namespace utility {

void inputDialog(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

// TODO: Move tests into a seperate file

// Unit test for "invertMatrix" function
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

/*
 * The block name must be a valid file name too
 */
bool isValidBlockName(const QString blockName)
{
    // TODO: Add extra validation, such as filename length
    // True if fileName only contains alphanumeric characters
    QRegularExpression re("^[A-Za-z]+$"); // Contains alphanumeric characters only
    QRegularExpressionMatch match = re.match(blockName);
    return match.hasMatch();
}

} } // utility, je
