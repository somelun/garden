#pragma once

#include <cstdint>

//////////////////
// vec2

template<typename T>
struct vec2 {
    vec2() : x(0), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}

    inline vec2<T> operator+(const vec2<T>& v) {
        return vec2<T>(x + v.x, y + v.y);
    }

    inline vec2<T> operator-(const vec2<T>& v) {
        return vec2<T>(x - v.x, y - v.y);
    }

    inline vec2<T> operator*(float f) {
        return vec2<T>(x * f, y * f);
    }

    T x;
    T y;
};

using Point = vec2<int>;

//////////////////
// vec3

template<typename T>
struct vec3 {
    vec3() : x(0), y(0), z(0) {}
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    inline vec3<T> operator+(const vec3<T>& v) {
        return vec3<T>(x + v.x, y + v.y, z + v.z);
    }

    inline vec3<T> operator-(const vec3<T>& v) {
        return vec3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline vec3<T> operator*(float f) {
        return vec3<T>(x * f, y * f, z * f);
    }

    // inline T& operator[](int i) {
    //     return raw[i];
    // }

    inline vec3<T>& operator=(const vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    inline float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    inline vec3<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }

    T x;
    T y;
    T z;
};

template<typename T>
inline float dot(const vec3<T>& v1, const vec3<T>& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y()  + v1.z() * v2.z();
}

template<typename T>
inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>((v1.y() * v2.z() - v1.z() * v2.y()),
                (-(v1.x() * v2.z() - v1.z() * v2.x())),
                (v1.x() * v2.y() - v1.y() * v2.x()));
}

//////////////////
// vec4

template<typename T>
struct vec4 {
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    inline vec4<T> operator+(const vec4<T>& v) {
        return vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    inline vec4<T> operator-(const vec4<T>& v) {
        return vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    inline vec4<T> operator*(float f) {
        return vec4<T>(x * f, y * f, z * f, w * f);
    }

    inline T& operator[](int i) {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
        }
    }

    inline const T& operator[](int i) const {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
        }
    }

    inline vec4<T>& operator=(const vec4<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    inline float length() const {
        return sqrt(x * x + y * y + z * z * w * w);
    }

    inline vec4<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }

    T x;
    T y;
    T z;
    T w;
};

using Color = vec4<uint8_t>;
using vec4f = vec4<float>;
