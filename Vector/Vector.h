#pragma once
#include <vector>

class Vector
{  
private:
    std::vector<double> m_vector;
    std::vector<double> m_direction;
    double m_magnitude;

    bool m_needsUpdate;

    void recalculateVector();

public:
    Vector();
    Vector(std::vector<double> vect);

    void addElement(double element);
    static double dotProduct(Vector& vectorA, Vector& vectorB);
    static Vector crossProduct(const Vector& vectorA, const Vector& vectorB);

    std::vector<double> getVector() const;
    size_t getSize() const;
    Vector getDirection();
    double getMagnitude();
    void printVector() const;
};
