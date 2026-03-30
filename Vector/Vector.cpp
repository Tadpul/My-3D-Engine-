#include <iostream>
#include <array>
#include <initializer_list>
#include <cmath>

template <size_t Dimensions>
class Vector
{
private:
    std::array<double, Dimensions> m_vector;

public:
    // constructors
    Vector() : m_vector({}) {}
    Vector(std::array<double, Dimensions> vector) : m_vector(std::move(vector)) {}
    
    // static functions
    static double dotProduct(const Vector<Dimensions>& v1, const Vector<Dimensions>& v2) 
    {
        double result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result += v1.m_vector[i] * v2.m_vector[i]; }
        return result;
    }

    // simple return functions
    double getMagnitude() const 
    {
        double squaredSum{ 0 };
        for (double num : m_vector) { squaredSum += std::pow(num, 2); }
        return std::sqrt(squaredSum);
    }

    Vector<Dimensions> getDirection() const 
    {
        double magnitude{ getMagnitude() };
        std::array<double, Dimensions> direction{};
        for (size_t i{ 0 }; i < Dimensions; i++) { direction[i] = m_vector[i] / magnitude; }
        return Vector<Dimensions>(direction);
    }

    void printVector() const
    {
        for (double element : m_vector) { std::cout << element << ' '; }
        std::cout << '\n';
    }

    // accessor functions
    double& x()
    {
        static_assert(Dimensions >= 1 && Dimensions < 5, "Dimensions must be from 1 - 4");
        return m_vector[0];
    }

    double& y()
    {
        static_assert(Dimensions >= 1 && Dimensions < 5, "Dimensions must be from 1 - 4");
        return m_vector[1];
    }

    double& z()
    {
        static_assert(Dimensions >= 1 && Dimensions < 5, "Dimensions must be from 1 - 4");
        return m_vector[2];
    }   

    double& w()
    {
        static_assert(Dimensions >= 1 && Dimensions < 5, "Dimensions must be from 1 - 4");
        return m_vector[3];
    }

    // overload access function
    double& operator()(size_t i) { return m_vector[i]; }

    // general operator overloads
    friend Vector<Dimensions> operator+(const Vector<Dimensions>& vectorA, const Vector<Dimensions>& vectorB)
    {
        std::array<double, Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result[i] = vectorA.m_vector[i] + vectorB.m_vector[i]; }
        return Vector(result);
    }

    friend Vector<Dimensions> operator-(const Vector<Dimensions>& vectorA, const Vector<Dimensions>& vectorB)
    {
        std::array<double, Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result[i] = vectorA.m_vector[i] - vectorB.m_vector[i]; }
        return Vector(result);
    }

    friend Vector<Dimensions> operator*(const double& scalar, const Vector<Dimensions>& vector)
    {
        std::array<double, Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result[i] = scalar * vector.m_vector[i]; }
        return Vector(result);
    }

    friend Vector<Dimensions> operator*(const Vector<Dimensions>& vector, const double& scalar)
    {
        return (scalar * vector);
    }

    friend std::ostream& operator<<(std::ostream& os, Vector<Dimensions> vector)
    {
        for (double element : vector.m_vector) { os << element << ' '; }
        std::cout << '\n';
        return os;
    }
};

using Vec3 = Vector<3>;
