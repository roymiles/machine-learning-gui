#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

namespace je {

/*
 * --- DEPRECATED ---
 * This has been abandoned. Just use OpenCV. Was an interesting exercise though.
 */
template<class T>
class [[deprecated]] Matrix
{
public:
    Matrix() = delete; // Construct empty matrix
    Matrix(const std::vector<std::vector<T>> data, const int rows, const int cols) : _data(data), _rows(rows), _cols(cols)
    {
        assert("Deprecated" == "Hi");
        assert(rows * cols == data.size() * data[0].size());
    }

    const std::vector<std::vector<T>>& data() const
    {
        return _data;
    }

    const int rows() const
    {
        return _rows;
    }

    const int cols() const
    {
        return _cols;
    }

    void set(const int x, const int y, T val)
    {
        _data[y][x] = val;
    }

    // Pretty print the matrix
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        os << "{";
        // Loop through all rows
        auto data = mat.data();
        for(size_t y = 0; y < data.size(); y++) // Not range based to help with accessing last iteration
        {
            // Loop through all columns (elements)
            bool first = true;
            for(const T &elem : data[y])
            {
                if(!first) os << ", ";
                os << elem;
                first = false;
            }

            if(y != data.size()-1)
                os << "\n";
        }
        os << "}";
        return os;
    }

    template<typename T1, typename T2>
    Matrix<T1> operator*(const Matrix<T2>& rhs) const
    {
        // Multiply each row of the first matrix by the columns of the second matrix
        Matrix<T1> out;

        // The number of columns in the first matrix must equal the number of rows in the second
        assert(_cols == mat.rows());

        auto rhsd = mat.data();
        // Loop through rows of current instance
        for(size_t y = 0; y < _rows; y++)
        {
            // Loop through columns of mat
            for(size_t x = 0; x < mat.cols(); x++)
            {
                // Multiply and add each element in row and col vectors
                T1 val = 0;
                for(size_t n = 0; n < _cols; n++) // Alternatively, mat.rows()
                    val += (_data[y][n] * rhsd[n][x]);

                out.set(x, y, val);
            }
        }

        return out;
    }

    void print()
    {
        std::cout << this << std::endl;
    }

private:
    // A vector of column vectors. First index specifies the row index
    std::vector<std::vector<T>> _data;

    const int _cols, _rows;
};

} // je

#endif // MATRIX_H
