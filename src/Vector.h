#pragma once

#include <iostream>
#include <array>
#include <initializer_list>
#include <cmath>
#include <cassert>

template <size_t Dimensions>
class Vector
{
private:
    std::array<float, Dimensions> m_vector{};

public:
    // constructors
    Vector() {}
    Vector(std::initializer_list<float> vector) 
    {
        assert(vector.size() == Dimensions && "Number of elements must match!");
        std::copy(vector.begin(), vector.end(), m_vector.begin());
    }
    Vector(std::array<float, Dimensions> vector) : m_vector(std::move(vector)) {}
    
    // static functions
    static float dotProduct(const Vector<Dimensions>& v1, const Vector<Dimensions>& v2) 
    {
        float result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result += v1.m_vector[i] * v2.m_vector[i]; }
        return result;
    }

    // simple return functions
    float getMagnitude() const 
    {
        float squaredSum{ 0 };
        for (float num : m_vector) { squaredSum += num * num; }
        return std::sqrt(squaredSum);
    }

    Vector<Dimensions> getDirection() const 
    {
        float magnitude{ getMagnitude() };
        Vector<Dimensions> direction{};
        for (size_t i{ 0 }; i < Dimensions; i++) { direction(i) = m_vector[i] / magnitude; }
        return direction;
    }

    void printVector() const
    {
        for (float element : m_vector) { std::cout << element << ' '; }
        std::cout << '\n';
    }

    // accessor functions
    float& x() requires (Dimensions >= 1) { return m_vector[0]; }
    float& y() requires (Dimensions >= 2) { return m_vector[1]; }
    float& z() requires (Dimensions >= 3) { return m_vector[2]; }
    float& w() requires (Dimensions >= 4) { return m_vector[3]; }

    // const accessor functions
    const float& x() const requires (Dimensions >= 1) { return m_vector[0]; }
    const float& y() const requires (Dimensions >= 2) { return m_vector[1]; }
    const float& z() const requires (Dimensions >= 3) { return m_vector[2]; }
    const float& w() const requires (Dimensions >= 4) { return m_vector[3]; }

    // overload access function
    float& operator()(size_t i) { return m_vector[i]; }
    const float& operator()(size_t i) const { return m_vector[i]; }

    // friend operator overloads
    friend Vector<Dimensions> operator+(const Vector<Dimensions>& vectorA, const Vector<Dimensions>& vectorB) 
    {
        Vector<Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result(i) = vectorA.m_vector[i] + vectorB.m_vector[i]; }
        return result;
    }

    friend Vector<Dimensions> operator-(const Vector<Dimensions>& vectorA, const Vector<Dimensions>& vectorB)
    {
        Vector<Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result(i) = vectorA.m_vector[i] - vectorB.m_vector[i]; }
        return result;
    }

    friend Vector<Dimensions> operator*(const float& scalar, const Vector<Dimensions>& vector) 
    {
        Vector<Dimensions> result{};
        for (size_t i{ 0 }; i < Dimensions; i++) { result(i) = scalar * vector.m_vector[i]; }
        return result;
    }

    friend Vector<Dimensions> operator*(const Vector<Dimensions>& vector, const float& scalar) 
    {
        return (scalar * vector);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<Dimensions>& vector) 
    {
        for (float element : vector.m_vector) { os << element << ' '; }
        os << '\n';
        return os;
    }
};

// type alias
using Vec2 = Vector<2>;
using Vec3 = Vector<3>;
using Vec4 = Vector<4>;
