#include <iostream>
#include <cmath>
#include <cassert>
#include <array>

template <size_t Rows, size_t Columns>
class Matrix
{
private:
    std::array<double, Rows * Columns> matrix;

public:
    Matrix() : matrix({}) {}
    Matrix(std::array<double, Rows * Columns> mat) : matrix(std::move(mat)) {}

    void printMatrix() const 
    {
        for (size_t row{ 0 }; row < Rows; row++)
        {
            for (size_t column{ 0 }; column < Columns; column++)
            {
                std::cout << matrix[row * Columns + column] << ' ';
            }
            std::cout << '\n';
        }
    }

    static Matrix identity()
    {
        assert(Columns == Rows && "Columns must be equal to Rows!");

        std::array<double, Columns * Rows> identityMatrix{};
        for (size_t element{ 0 }; element < identityMatrix.size(); element += (Columns + 1))
        {
            identityMatrix[element] = 1;
        }

        return identityMatrix;
    }

    // in class operator overloads
    double& operator()(size_t row, size_t column)
    {
        return matrix[row * Columns + column];
    }

    const double& operator()(size_t row, size_t column) const
    {
        return matrix[row * Columns + column];
    }
};

template <size_t Rows, size_t Columns>
std::ostream& operator<<(std::ostream& os, const Matrix<Rows, Columns>& matrix)
{
    matrix.printMatrix();
    return os;
}

template <size_t Rows1, size_t Columns1, size_t Rows2, size_t Columns2>
Matrix<Rows1, Columns2> operator*(Matrix<Rows1, Columns1> m1, Matrix<Rows2, Columns2> m2)
{
    Matrix<Rows1, Columns2> result{};

    for (size_t row{ 0 }; row < Rows1; row++)
    {
        for (size_t column{ 0 }; column < Columns2; column++)
        {
            double elementSum{ 0 };
            for (size_t i{ 0 }; i < Columns1; i++) { elementSum += m1(row, i) * m2(i, column); }
            result(row, column) = elementSum;
        }
    }
    return result;
}