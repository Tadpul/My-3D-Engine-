#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

class Vector
{  
private:
    std::vector<double> m_vector;
    std::vector<double> m_direction;
    double m_magnitude;

    bool m_needsUpdate;

    void recalculateVector(std::vector<double>& vect)
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
    Vector() : m_vector({}), m_direction({}), m_magnitude(0), m_needsUpdate(false) {}
    Vector(std::vector<double> vect) : m_vector(std::move(vect)), m_needsUpdate(true) {}

    void addElement(double element)
    {
        m_vector.push_back(element);
        m_needsUpdate = true;
    }

    // static vector operation functions 
    static double dotProduct(Vector& vectorA, Vector& vectorB)
    {
        assert(vectorA.getSize() == vectorB.getSize() && "Vectors must have the same size!");

        double dotProduct{ 0 };
        for (size_t i( 0 ); i < vectorA.getSize(); i++)
        {
            dotProduct += (vectorA.getVector()[i] * vectorB.getVector()[i]);
        }

        return dotProduct;
    }

    static Vector crossProduct(const Vector& vectorA, const Vector& vectorB)
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
    const std::vector<double>& getVector() const { return m_vector; }
    size_t getSize() const { return m_vector.size(); }
    const std::vector<double>& getDirection()
    {
        if (m_needsUpdate)
        { 
            recalculateVector(m_vector);
            m_needsUpdate = false;
        }
        return m_direction;
    }

    double getMagnitude() 
    {
        if (m_needsUpdate)
        { 
            recalculateVector(m_vector);
            m_needsUpdate = false;
        }
        return m_magnitude;
    }

    void printVector() const
    {
        for (double element : m_vector)
        {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
};

// operator overloads
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

Vector operator*(int scalar, Vector vector)
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

int main()
{

}