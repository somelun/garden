#pragma once

#include <cstdint>
#include <iostream>
#include <math.h>

//////////////////
// vec2

template<typename T>
struct vec2 {
    vec2() : x(0), y(0) {}
    vec2(T x_, T y_) : x(x_), y(y_) {}

    inline vec2<T> operator+(const vec2<T>& v) {
        return vec2<T>(x + v.x, y + v.y);
    }

    inline vec2<T> operator-(const vec2<T>& v) {
        return vec2<T>(x - v.x, y - v.y);
    }

    inline vec2<T> operator*(float f) {
        return vec2<T>(x * f, y * f);
    }

    inline T& operator[](size_t i) const {
        if (i == 0) {
            return x;
        } else if (i == 1) {
            return y;
        } else {
            return 0;   //TODO: hanle error
        }
    }


    friend std::ostream& operator<<(std::ostream& s, const vec2& v) {
        s << v.x << " " << v.y;
        return s;
    }

    T x;
    T y;
};

using Point = vec2<int>;
using vec2f = vec2<float>;
using vec2i = vec2<int>;

//////////////////
// vec3

template<typename T>
struct vec3 {
    vec3() : x(0), y(0), z(0) {}
    vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

    vec3(const vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

    inline vec3<T> operator+(const vec3<T>& v) {
        return vec3<T>(x + v.x, y + v.y, z + v.z);
    }

    inline vec3<T> operator-(const vec3<T>& v) {
        return vec3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline vec3<T> operator*(float f) {
        return vec3<T>(x * f, y * f, z * f);
    }

    inline  T& operator[](int i) {
        if (i == 0) {
            return x;
        } else if (i == 1) {
            return y;
        } else if (i == 2) {
            return z;
        } else {
            return 0;   //TODO: hanle error
        }
    }

    // TODO: add asserts to all [] operators
    inline const T& operator[](int i) const {
        if (i == 0) {
            return x;
        } else if (i == 1) {
            return y;
        } else if (i == 2) {
            return z;
        } else {
            return 0;   //TODO: hanle error
        }
    }

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

    friend std::ostream& operator<<(std::ostream& s, const vec3& v) {
        s << v.x << " " << v.y << " " << v.z;
        return s;
    }

    T x;
    T y;
    T z;
};

template<typename T>
inline float dot(const vec3<T>& v1, const vec3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

template<typename T>
inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>((v1.y * v2.z - v1.z * v2.y),
                   (v1.z * v2.x - v1.x * v2.z),
                   (v1.x * v2.y - v1.y * v2.x));
}

using vec3i = vec3<int>;
using vec3f = vec3<float>;

//////////////////
// vec4

template<typename T>
struct vec4 {
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}

    vec4(const vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    vec4(const vec3<T>& v, const T& w_) : x(v.x), y(v.y), z(v.z), w(w_) {}

    inline vec4<T> operator+(const vec4<T>& v) {
        return vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    inline vec4<T> operator-(const vec4<T>& v) {
        return vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    inline vec4<T> operator*(const float f) {
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
        }
        return w;
    }

    inline const T& operator[](int i) const {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
        }
        return w;
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

    friend std::ostream& operator<<(std::ostream& s, const vec4& v) {
        s << v.x << " " << v.y << " " << v.z << " " << v.w;
        return s;
    }

    T x;
    T y;
    T z;
    T w;
};

using Color = vec4<uint8_t>;
using vec4f = vec4<float>;
