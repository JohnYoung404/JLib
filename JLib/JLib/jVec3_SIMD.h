#pragma once
#include <emmintrin.h>  //SSE2
#include <immintrin.h>  //AVX
#include <array>

namespace jLib {
    namespace jContainer {

        template<typename Type>
        class jVec3_SIMD
        {
        public:
            constexpr jVec3_SIMD(Type x_ = 0, Type y_ = 0, Type z_ = 0) : _arr{ x_, y_, z_ } {}
            constexpr jVec3_SIMD(const jVec3_SIMD &rhs) : _arr(rhs._arr) {}
            constexpr jVec3_SIMD(jVec3_SIMD && rhs) : _arr(std::move(rhs._arr)) {}
            jVec3_SIMD& operator= (const jVec3_SIMD &rhs)
            {
                _arr = rhs._arr;
                return *this;
            }
            jVec3_SIMD& operator= (jVec3_SIMD && rhs)
            {
                _arr = std::move(rhs._arr);
                return *this;
            }
            inline static constexpr const jVec3_SIMD zero() { return jVec3_SIMD(); }

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

            jVec3_SIMD operator+(const jVec3_SIMD &b) const { return jVec3_SIMD(x() + b.x(), y() + b.y(), z() + b.z()); }        // Addition
            jVec3_SIMD operator-(const jVec3_SIMD &b) const { return jVec3_SIMD(x() - b.x(), y() - b.y(), z() - b.z()); }        // Subtraction
            jVec3_SIMD operator*(Type b) const { return jVec3_SIMD(x() * b, y() * b, z() * b); }                  // Multiplaction with scalar
            Type operator*(const jVec3_SIMD &b) const { return this->dot(b); }
            jVec3_SIMD operator/(Type b) const { return jVec3_SIMD(x() / b, y() / b, z() / b); }            // Division with scalar
            jVec3_SIMD mult(const jVec3_SIMD &b) const { return jVec3_SIMD(x() * b.x(), y() * b.y(), z() * b.z()); }             // Multiplication
            const jVec3_SIMD normalize() const { return *this * (Type(1) / sqrt(x() * x() + y() * y() + z() * z())); }                // Normalise vector
            Type  dot(const jVec3_SIMD &b) const { return x() * b.x() + y() * b.y() + z() * b.z(); }                // Dot product
            jVec3_SIMD cross(const jVec3_SIMD &b) const { return jVec3_SIMD(y() * b.z() - z() * b.y(), z() * b.x() - x() * b.z(), x() * b.y() - y() * b.x()); }    // Cross product

            template<typename Type>
            inline friend Type dot(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b);
            template<typename Type>
            inline friend jVec3_SIMD<Type> cross(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b);
            template<typename Type>
            inline friend jVec3_SIMD<Type> mult(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b);
        private:
            std::array<Type, 3> _arr;
        };

        template <typename Type>
        std::ostream& operator<< (std::ostream& os, const jVec3_SIMD<Type> &outVec) {
            for (int i = 0; i < 3; ++i)
            {
                std::cout << outVec[i] << " ";
            }
            std::cout << std::endl;
            return os;
        }

        template<typename Type>
        Type dot(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b)
        {
            return a.dot(b);
        }

        template<typename Type>
        jVec3_SIMD<Type> cross(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b)
        {
            return a.cross(b);
        }

        template<typename Type>
        jVec3_SIMD<Type> mult(const jVec3_SIMD<Type> &a, const jVec3_SIMD<Type> &b)
        {
            return a.mult(b);
        }

    }
}