#pragma once

///////////////////////////////////////////////////////////
// vector3

template<typename T>
struct vector3 {
    union {
        struct { T x, y, z; };
        T raw[3];
    };

    vector3() : x(0), y(0), z(0) {}
    vector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

inline vector3<T> operator+(const vector3<T>& v) {
        return vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    inline vector3<T> operator-(const vector3<T>& v) {
        return vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline vector3<T> operator*(float f) {
        return vector3<T>(x * f, y * f, z * f);
    }

    inline T& operator[](int i) {
        return raw[i];
    }

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
};

template<typename T>
inline float dot(const vector3<T>& v1, const vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

template<typename T>
inline vector3<T> cross(const vector3<T>& v1, const vector3<T>& v2) {
    return vector3<T>((v1.y * v2.z - v1.z * v2.y),
                (-(v1.x * v2.z - v1.z * v2.x)),
                (v1.x * v2.y - v1.y * v2.x));
}

///////////////////////////////////////////////////////////
// vector4

template<typename T>
struct vector4 {
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        T raw[4];
    };

    vector4() : x(0), y(0), z(0), w(0) {}
    vector4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}

inline vector4<T> operator+(const vector4<T>& v) {
        return vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    inline vector4<T> operator-(const vector4<T>& v) {
        return vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    inline vector4<T> operator*(float f) {
        return vector4<T>(x * f, y * f, z * f, w * f);
    }

    inline T& operator[](int i) {
        return raw[i];
    }

    inline vector4<T>& operator=(const vector4<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    inline float length() const {
        return sqrt(x * x + y * y + z * z * w * w);
    }

    inline vector4<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }
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

using color = vector4<uint8_t>;
