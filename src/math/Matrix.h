#pragma once

#include "Vector.h"
#include "../object3D/Camera.h"

template <size_t Rows, size_t Columns>
class Matrix
{
private:
    std::array<float, Rows * Columns> m_matrix{};

public:
    // constructors
    Matrix() {}
    Matrix(std::initializer_list<float> matrix) 
    {
        assert(matrix.size() == (Rows * Columns) && "Number of elements must match!");
        std::copy(matrix.begin(), matrix.end(), m_matrix.begin());
    }
    Matrix(std::array<float, Rows * Columns> mat) : m_matrix(std::move(mat)) {}

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

    // static member variables
    static Matrix identity() 
    {
        static_assert(Columns == Rows, "Columns must be equal to Rows!");

        std::array<float, Columns * Rows> identityMatrix{};
        for (size_t element{ 0 }; element < identityMatrix.size(); element += (Columns + 1))
        {
            identityMatrix[element] = 1;
        }

        return Matrix(identityMatrix);
    }

    static Matrix<4, 4> scale(float x, float y, float z) 
    {
        Matrix<4, 4> result{ identity() };
        result(0, 0) = x;
        result(1, 1) = y;
        result(2, 2) = z;
        result(3, 3) = 1;
        return result;
    }

    static Matrix<4, 4> rotateX(float angle)
    {
        Matrix<4, 4> result{ identity() };
        result(1, 1) =  std::cos(angle);
        result(1, 2) = -std::sin(angle);
        result(2, 1) =  std::sin(angle);
        result(2, 2) =  std::cos(angle);
        return result;
    }

    static Matrix<4, 4> rotateY(float angle)
    {
        Matrix<4, 4> result{ identity() };
        result(0, 0) =  std::cos(angle);
        result(0, 2) =  std::sin(angle);
        result(2, 0) = -std::sin(angle);
        result(2, 2) =  std::cos(angle);
        return result;
    }

    static Matrix<4, 4> rotateZ(float angle)
    {
        Matrix<4, 4> result{ identity() };
        result(0, 0) =  std::cos(angle);
        result(0, 1) = -std::sin(angle);
        result(1, 0) =  std::sin(angle);
        result(1, 1) =  std::cos(angle);
        return result;
    }

    static Matrix<4, 4> projection(float l, float r, float b, float t, float n, float f)
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

    static Matrix<4, 4> projection(float fovDegrees, float aspect, float n, float f)
    {
        float halfH = n * std::tan(fovDegrees * std::acos(-1) / 180.0f * 0.5f);
        float halfW = halfH * aspect;
        return projection(-halfW, halfW, -halfH, halfH, n, f);
    }

    static Matrix<4, 4> translate(float x, float y, float z)
    {
        Matrix<4, 4> translationMatrix{ identity() };
        translationMatrix(0, 3) = x;
        translationMatrix(1, 3) = y;
        translationMatrix(2, 3) = z;

        return translationMatrix;
    }

    // in class operator overloads
    float& operator()(size_t row, size_t column)
    {
        return m_matrix[row * Columns + column];
    }

    const float& operator()(size_t row, size_t column) const
    {
        return m_matrix[row * Columns + column];
    }

    // friend operator overloads
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

    friend Matrix<Rows, Columns> operator*(const float& scalar, const Matrix<Rows, Columns>& matrix)
    {
        Matrix<Rows, Columns> result{};
        for (size_t i{ 0 }; i < result.m_matrix.size(); i++) { result.m_matrix[i] = scalar * matrix.m_matrix[i]; }

        return result;
    }

    friend Matrix<Rows, Columns> operator*(const Matrix<Rows, Columns>& matrix, const float& scalar)
    {
        return (scalar * matrix);
    }
};

// matrix * matrix multiplication
template <size_t Rows1, size_t Columns1, size_t Rows2, size_t Columns2>
Matrix<Rows1, Columns2> operator*(const Matrix<Rows1, Columns1>& m1, const Matrix<Rows2, Columns2>& m2)
{
    static_assert(Columns1 == Rows2, "These matrices arent multiplyable!");

    Matrix<Rows1, Columns2> result{};

    for (size_t row{ 0 }; row < Rows1; row++)
    {
        for (size_t column{ 0 }; column < Columns2; column++)
        {
            for (size_t i{ 0 }; i < Columns1; i++) { result(row, column) += m1(row, i) * m2(i, column); }
        }
    }
    return result;
}

// matrix * vector multiplication
template <size_t Rows, size_t Columns, size_t Dimensions>
Vector<Dimensions> operator*(const Matrix<Rows, Columns>& matrix, const Vector<Dimensions>& vector)
{
    Vector<Dimensions> result{};
    for (size_t row{ 0 }; row < Rows; row++)
    {
        for (size_t column{ 0 }; column < Columns; column++) { result(row) += matrix(row, column) * vector(column); }
    }
    return result;
}

inline Matrix<4, 4> getViewMatrix(const Camera& cam) 
{
    Matrix<4, 4> result;
    Matrix<4, 4> rotationY = Matrix<4, 4>::rotateY(-cam.yaw);
    Matrix<4, 4> rotationX = Matrix<4, 4>::rotateX(-cam.pitch);
    Matrix<4, 4> translation = Matrix<4, 4>::translate(-cam.position.x(), -cam.position.y(), -cam.position.z());

    result = rotationX * rotationY * translation;

    return result;
}

// type alias
using Mat3 = Matrix<3, 3>;
using Mat4 = Matrix<4, 4>;
