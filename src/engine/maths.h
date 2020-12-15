// TODO: split this file into math/vec2, math/vec3, etc
#pragma once

#include <cstdint>
#include <iostream>

///////////////////////////////////////////////////////////
// vector2

template<typename T>
struct vector2 {
    vector2() : x(0), y(0) {
        std::cout << "vector2()" << std::endl;
    }
    vector2(T x, T y) : x(x), y(y) {
        std::cout << "vector2(" << x << ", " << y << ")" << std::endl;
    }

    inline vector2<T> operator+(const vector2<T>& v) {
        return vector2<T>(x + v.x, y + v.y);
    }

    inline vector2<T> operator-(const vector2<T>& v) {
        return vector2<T>(x - v.x, y - v.y);
    }

    inline vector2<T> operator*(float f) {
        return vector2<T>(x * f, y * f);
    }

    T x;
    T y;
};

using vector2i = vector2<int>;
using Point = vector2<int>;

///////////////////////////////////////////////////////////
// vector3

template<typename T>
struct vector3 {
    vector3() : x(0), y(0), z(0) {}
    vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    inline vector3<T> operator+(const vector3<T>& v) {
        return vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    inline vector3<T> operator-(const vector3<T>& v) {
        return vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline vector3<T> operator*(float f) {
        return vector3<T>(x * f, y * f, z * f);
    }

    // inline T& operator[](int i) {
    //     return raw[i];
    // }

    inline vector3<T>& operator=(const vector3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    inline float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    inline vector3<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }

    T x;
    T y;
    T z;
};

template<typename T>
inline float dot(const vector3<T>& v1, const vector3<T>& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y()  + v1.z() * v2.z();
}

template<typename T>
inline vector3<T> cross(const vector3<T>& v1, const vector3<T>& v2) {
    return vector3<T>((v1.y() * v2.z() - v1.z() * v2.y()),
                (-(v1.x() * v2.z() - v1.z() * v2.x())),
                (v1.x() * v2.y() - v1.y() * v2.x()));
}

using vector3f = vector3<float>;
using vector3i = vector3<int>;

///////////////////////////////////////////////////////////
// vector4

template<typename T>
struct vector4 {
    vector4() : x_(0), y_(0), z_(0), w_(0) {}
    vector4(T x, T y, T z, T w) : x_(x), y_(y), z_(z), w_(w) {}

    inline vector4<T> operator+(const vector4<T>& v) {
        return vector4<T>(x_ + v.x(), y_ + v.y(), z_ + v.z(), w_ + v.w());
    }

    inline vector4<T> operator-(const vector4<T>& v) {
        return vector4<T>(x_ - v.x(), y_ - v.y(), z_ - v.z(), w_ - v.w());
    }

    inline vector4<T> operator*(float f) {
        return vector4<T>(x_ * f, y_ * f, z_ * f, w_ * f);
    }

    // inline T& operator[](int i) {
    //     return raw[i];
    // }

    // inline const T& operator[](int i) const {
    //     return raw[i];
    // }

    inline vector4<T>& operator=(const vector4<T>& v) {
        x_ = v.x();
        y_ = v.y();
        z_ = v.z();
        w_ = v.w();
        return *this;
    }

    inline float length() const {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_ * w_ * w_);
    }

    inline vector4<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }

    const T& x() const { return x_; }
    const T& y() const { return y_; }
    const T& z() const { return z_; }
    const T& w() const { return w_; }

    // sugar
    const T& r() const { return x_; }
    const T& g() const { return y_; }
    const T& b() const { return z_; }
    const T& a() const { return w_; }
private:
    T x_;
    T y_;
    T z_;
    T w_;
};

// template<typename T>
// inline float dot(const vector4<T>& v1, const vector4<T>& v2) {
//     return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
// }

// template<typename T>
// inline vector4<T> cross(const vector4<T>& v1, const vector4<T>& v2) {
//     return vector4<T>((v1.y * v2.z - v1.z * v2.y),
//                 (-(v1.x * v2.z - v1.z * v2.x)),
//                 (v1.x * v2.y - v1.y * v2.x));
// }

using Color = vector4<uint8_t>;
