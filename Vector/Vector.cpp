#include <vector>
#include <cmath>
#include <iostream>

class Vector
{  
private:
    std::vector<double> m_vector;
    std::vector<double> m_direction;
    double m_magnitude;

    void recalculateVector(const std::vector<double>& vect)
    {
        // reinitialise the vector of this class
        m_vector = vect;    

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

public:
    Vector() : m_vector({}), m_direction({}), m_magnitude(0) {}
    Vector(const std::vector<double>& vect) { recalculateVector(vect); }
    void addElement(double element)
    {
        m_vector.push_back(element);
        recalculateVector(m_vector);
    }

    const std::vector<double>& getVector() const { return m_vector; }
    const std::vector<double>& getDirection() const { return m_direction; }
    double getMagnitude() const { return m_magnitude; }
    int getSize() const { return m_vector.size(); }

    void printVector() const
    {
        for (double element : m_vector)
        {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
};

double dotProduct(const std::vector<double>& vectorA, const std::vector<double>& vectorB)
{
    if (vectorA.size() == vectorB.size())
    {
        double dotProduct{ 0 };
        for (size_t i( 0 ); i < vectorA.size(); i++)
        {
            dotProduct += (vectorA[i] * vectorB[i]);
        }

        return dotProduct;
    }
    return static_cast<double>(INT_MIN);
}

double dotProduct(Vector& vectorA, Vector& vectorB)
{
    if (vectorA.getSize() == vectorB.getSize())
    {
        double dotProduct{ 0 };
        for (size_t i( 0 ); i < vectorA.getSize(); i++)
        {
            dotProduct += (vectorA.getVector()[i] * vectorB.getVector()[i]);
        }

        return dotProduct;
    }
    return static_cast<double>(INT_MIN);
}

std::vector<double>& crossProduct(const std::vector<double>& vectorA, const std::vector<double>& vectorB)
{
    if (vectorA.size() == vectorB.size())
    {
        std::vector<double> vector1 = vectorA;
        std::vector<double> vector2 = vectorB;

        if (vectorA.size() == 2)
        {
            vector1.push_back(0);
            vector2.push_back(0);
        }

        std::vector<double> crossProduct(3, 0.0);
        crossProduct[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
        crossProduct[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
        crossProduct[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];

        return crossProduct;
    }
    return std::vector<double>(3, static_cast<double>(INT_MIN));
}

std::vector<double>& crossProduct(const Vector& vectorA, const Vector& vectorB)
{
    if (vectorA.getSize() == vectorB.getSize())
    {
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

        return crossProduct;
    }
    return std::vector<double>(3, static_cast<double>(INT_MIN));
}

template <typename type>
std::ostream& operator<<(std::ostream& os, const std::vector<type>& vect)
{
    for (type element : vect) { os << element << ' '; }
    os << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vector& vect)
{
    vect.printVector();
    return os;
}