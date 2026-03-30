#include <iostream>
#include <cmath>
#include <cassert>
#include <array>
#include <initializer_list>

template <size_t Rows, size_t Columns>
class Matrix
{
private:
    std::array<double, Rows * Columns> m_matrix{};

public:
    Matrix() {}
    Matrix(std::initializer_list<double> matrix) 
    {
        assert(matrix.size() == (Rows * Columns) && "Number of elements must match!");
        std::copy(matrix.begin(), matrix.end(), m_matrix.begin());
    }
    Matrix(std::array<double, Rows * Columns> mat) : m_matrix(std::move(mat)) {}

    void printMatrix() const 
    {
        for (size_t row{ 0 }; row < Rows; row++)
        {
            for (size_t column{ 0 }; column < Columns; column++)
            {
                std::cout << m_matrix[row * Columns + column] << ' ';
            }
            std::cout << '\n';
        }
    }

    static Matrix identity()
    {
        static_assert(Columns == Rows && "Columns must be equal to Rows!");

        std::array<double, Columns * Rows> identityMatrix{};
        for (size_t element{ 0 }; element < identityMatrix.size(); element += (Columns + 1))
        {
            identityMatrix[element] = 1;
        }

        return Matrix(identityMatrix);
    }

    static Matrix scalar(double scalar) { return (scalar * identity()); }

    static Matrix<4, 4> projection(double l, double r, double b, double t, double n, double f)
    {
        Matrix<4, 4> projectionMatrix{};
        projectionMatrix(0, 0) = 2 * n / (r - l);
        projectionMatrix(0, 2) = (l + r) / (r - l);
        projectionMatrix(1, 1) = 2 * n / (t - b);
        projectionMatrix(1, 2) = (b + t) / (t - b);
        projectionMatrix(2, 2) = -(f + n) / (f - n);
        projectionMatrix(2, 3) = -2 * f * n / (f - n);
        projectionMatrix(3, 2) = -1;

        return projectionMatrix;
    }

    // in class operator overloads
    double& operator()(size_t row, size_t column)
    {
        return m_matrix[row * Columns + column];
    }

    const double& operator()(size_t row, size_t column) const
    {
        return m_matrix[row * Columns + column];
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<Rows, Columns>& matrix)
    {
        for (size_t row{ 0 }; row < Rows; row++)
        {
            for (size_t column{ 0 }; column < Columns; column++)
            {
                os << matrix.m_matrix[row * Columns + column] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    friend Matrix<Rows, Columns> operator+(const Matrix<Rows, Columns>& m1, const Matrix<Rows, Columns>& m2)
    {
        Matrix<Rows, Columns> result{};
        for (size_t i{ 0 }; i < result.m_matrix.size(); i++) { result.m_matrix[i] = (m1.m_matrix[i] + m2.m_matrix[i]); }
        
        return result;
    }

    friend Matrix<Rows, Columns> operator-(const Matrix<Rows, Columns>& m1, const Matrix<Rows, Columns>& m2)
    {
        Matrix<Rows, Columns> result{};
        for (size_t i{ 0 }; i < result.m_matrix.size(); i++) { result.m_matrix[i] = (m1.m_matrix[i] - m2.m_matrix[i]); }

        return result;
    }

    friend Matrix<Rows, Columns> operator*(const double& scalar, const Matrix<Rows, Columns>& matrix)
    {
        Matrix<Rows, Columns> result{};
        for (size_t i{ 0 }; i < result.m_matrix.size(); i++) { result.m_matrix[i] = scalar * matrix.m_matrix[i]; }

        return result;
    }

    friend Matrix<Rows, Columns> operator*(const Matrix<Rows, Columns>& matrix, const double& scalar)
    {
        return (scalar * matrix);
    }
};

template <size_t Rows1, size_t Columns1, size_t Rows2, size_t Columns2>
Matrix<Rows1, Columns2> operator*(const Matrix<Rows1, Columns1>& m1, const Matrix<Rows2, Columns2>& m2)
{
    static_assert(Columns1 == Rows2 && "These matrices arent multiplyable!");

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

using Mat3 = Matrix<3, 3>;
using Mat4 = Matrix<4, 4>;
