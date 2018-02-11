#pragma once

#include <array>

namespace jLib{
namespace jContainer{

template<typename Type>
class jVec3
{
public:
    constexpr jVec3(Type x_ = 0, Type y_ = 0, Type z_ = 0) : _arr{x_, y_, z_} {}
    constexpr jVec3(const jVec3 &rhs) : _arr(rhs._arr) {}
    constexpr jVec3(jVec3 && rhs) : _arr(std::move(rhs._arr)) {}
    jVec3& operator= (const jVec3 &rhs)
    {
        _arr = rhs._arr;
        return *this;
    }
    jVec3& operator= (jVec3 && rhs) 
    {
        _arr = std::move(rhs._arr);
        return *this;
    }
    inline static constexpr const jVec3 zero() { return jVec3(); }

    inline const Type& x() const { return _arr[0]; }
    inline const Type& y() const { return _arr[1]; }
    inline const Type& z() const { return _arr[2]; }
    inline Type& x() { return _arr[0]; }
    inline Type& y() { return _arr[1]; }
    inline Type& z() { return _arr[2]; }

    const Type & at(size_t pos) const { return _arr.at(pos); }
    Type & at(size_t pos) { return _arr.at(pos); }
    const Type & operator[](size_t pos) const { return _arr[pos]; }
    Type & operator[](size_t pos) { return _arr[pos]; }

    inline const Type square_length() const
    {
        return (*this) * (*this);
    }

    jVec3 operator+(const jVec3 &b) const { return jVec3(x() + b.x(), y() + b.y(), z() + b.z()); }        // Addition
    jVec3 operator-(const jVec3 &b) const { return jVec3(x() - b.x(), y() - b.y(), z() - b.z()); }        // Subtraction
    jVec3 operator*(Type b) const { return jVec3(x() * b, y() * b, z() * b); }                  // Multiplaction with scalar
    Type operator*(const jVec3 &b) const { return this->dot(b); }
    jVec3 operator/(Type b) const { return jVec3(x() / b, y() / b, z() / b); }            // Division with scalar
    jVec3 mult(const jVec3 &b) const { return jVec3(x() * b.x(), y() * b.y(), z() * b.z()); }             // Multiplication
    //const jVec3 normalize() const { return *this * (Type(1) / sqrt(x() * x() + y() * y() + z() * z())); }                // Normalise vector
    Type  dot(const jVec3 &b) const { return x() * b.x() + y() * b.y() + z() * b.z(); }                // Dot product
    jVec3 cross(const jVec3 &b) const { return jVec3(y() * b.z() - z() * b.y(), z() * b.x() - x() * b.z(), x() * b.y() - y() * b.x()); }    // Cross product

    jVec3& normalize() {
        Type scarlar = (Type(1) / sqrt(x() * x() + y() * y() + z() * z()));
        this->x() *= scarlar;
        this->y() *= scarlar;
        this->z() *= scarlar;
        return *this;
    }                // Normalise vector

    template<typename Type>
    inline friend Type dot (const jVec3<Type> &a, const jVec3<Type> &b);
    template<typename Type>
    inline friend jVec3<Type> cross(const jVec3<Type> &a, const jVec3<Type> &b);
    template<typename Type>
    inline friend jVec3<Type> mult(const jVec3<Type> &a, const jVec3<Type> &b);
private:
    std::array<Type, 3> _arr;
};

template <typename Type>
std::ostream& operator<< (std::ostream& os, const jVec3<Type> &outVec) {
    for (int i = 0; i < 3; ++i)
    {
        std::cout << outVec[i] << " ";
    }
    std::cout << std::endl;
    return os;
}

template<typename Type>
Type dot (const jVec3<Type> &a, const jVec3<Type> &b)
{
    return a.dot(b);
}

template<typename Type>
jVec3<Type> cross(const jVec3<Type> &a, const jVec3<Type> &b)
{
    return a.cross(b);
}

template<typename Type>
jVec3<Type> mult(const jVec3<Type> &a, const jVec3<Type> &b)
{
    return a.mult(b);
}

}}