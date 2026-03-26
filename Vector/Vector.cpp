#include "Vector.h"
#include <cmath>
#include <cassert>

void Vector::recalculateVector()
{
    // recalculate the magnitude of this new vector
    double squaredSum{ 0 };
    for (double num : m_vector) { squaredSum += std::pow(num, 2); }
    m_magnitude = std::sqrt(squaredSum);

    // recalculate the direction of this vector
    m_direction.resize(m_vector.size(), 0.0);
    if (m_magnitude)
    {
        for (size_t i{ 0 }; i < m_vector.size(); i++)
        {
            m_direction[i] = m_vector[i] / m_magnitude;
        }
    }
}

Vector::Vector() : m_vector({}), m_direction({}), m_magnitude(0), m_needsUpdate(false) {}
Vector::Vector(std::vector<double> vect) : m_vector(std::move(vect)), m_needsUpdate(true) {}

void Vector::addElement(double element)
{
    m_vector.push_back(element);
    m_needsUpdate = true;
}

// static vector operation functions 
double Vector::dotProduct(Vector& vectorA, Vector& vectorB)
{
    assert(vectorA.getSize() == vectorB.getSize() && "Vectors must have the same size!");

    double dotProduct{ 0 };
    for (size_t i( 0 ); i < vectorA.getSize(); i++)
    {
        dotProduct += (vectorA.getVector()[i] * vectorB.getVector()[i]);
    }

    return dotProduct;
}

Vector Vector::crossProduct(const Vector& vectorA, const Vector& vectorB)
{
    assert(vectorA.getSize() == vectorB.getSize() && (vectorA.getSize() == 2 || vectorA.getSize() == 3) && "Vectors must have the same size!");

    std::vector<double> vector1 = vectorA.getVector();
    std::vector<double> vector2 = vectorB.getVector();

    if (vectorA.getSize() == 2)
    {
        vector1.push_back(0);
        vector2.push_back(0);
    }

    std::vector<double> crossProduct(3, 0.0);
    crossProduct[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    crossProduct[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    crossProduct[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];

    if (vectorA.getSize() == 2) crossProduct.resize(2);
    return Vector(crossProduct);
}

// simple return functions
std::vector<double> Vector::getVector() const { return m_vector; }
size_t Vector::getSize() const { return m_vector.size(); }
Vector Vector::getDirection()
{
    if (m_needsUpdate)
    { 
        recalculateVector();
        m_needsUpdate = false;
    }
    return m_direction;
}

double Vector::getMagnitude() 
{
    if (m_needsUpdate)
    { 
        recalculateVector();
        m_needsUpdate = false;
    }
    return m_magnitude;
}

void Vector::printVector() const
{
    for (double element : m_vector)
    {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

std::ostream& operator<<(std::ostream& os, const Vector& vect)
{
    vect.printVector();
    return os;
}

Vector operator+(const Vector& vectorA, const Vector& vectorB)
{
    assert(vectorA.getSize() == vectorB.getSize() && "Vectors must be the same size!");

    std::vector<double> resultVector(vectorA.getSize());
    for (size_t i{ 0 }; i < vectorA.getSize(); i++)
    {
        resultVector[i] = vectorA.getVector()[i] + vectorB.getVector()[i];
    }
    return Vector(resultVector);
}

Vector operator-(const Vector& vectorA, const Vector& vectorB)
{
    assert(vectorA.getSize() == vectorB.getSize() && "Vectors must be the same size!");

    std::vector<double> resultVector(vectorA.getSize());
    for (size_t i{ 0 }; i < vectorA.getSize(); i++)
    {
        resultVector[i] = vectorA.getVector()[i] - vectorB.getVector()[i];
    }
    return Vector(resultVector);
}

Vector operator*(float scalar, Vector vector)
{
    std::vector<double> resultVector(vector.getSize());
    for (size_t i{ 0 }; i < vector.getSize(); i++)
    {
        resultVector[i] = scalar * vector.getVector()[i];
    }
    return Vector(resultVector);
}

Vector operator*(Vector vector, int scalar)
{
    return scalar * vector;
}
