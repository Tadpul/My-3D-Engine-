#pragma once
#include <vector>
#include <iostream>

class Vector
{  
private:
    std::vector<double> m_vector;
    std::vector<double> m_direction;
    double m_magnitude;

    bool m_needsUpdate;

    void recalculateVector();

public:
    // vector constructors
    Vector();
    Vector(std::vector<double> vect);

    // vector member functions
    void addElement(double element);
    static double dotProduct(Vector& vectorA, Vector& vectorB);
    static Vector crossProduct(const Vector& vectorA, const Vector& vectorB);

    // simple vector return functions
    std::vector<double> getVector() const;
    size_t getSize() const;
    Vector getDirection();
    double getMagnitude();
    void printVector() const;

    // in function operator overloads
    double& operator()(size_t element);
    const double& operator()(size_t element) const;
};

// operator overloads
std::ostream& operator<<(std::ostream& os, const Vector& vect);
Vector operator+(const Vector& vectorA, const Vector& vectorB);
Vector operator-(const Vector& vectorA, const Vector& vectorB);
Vector operator*(float scalar, Vector vector);
Vector operator*(Vector vector, int scalar);
