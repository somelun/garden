#pragma once

template<typename T>
struct Vector3 {
    union {
        struct { T x, y, z; };
        T raw[3];
    };

    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

inline Vector3<T> operator+(const Vector3<T>& v) {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    inline Vector3<T> operator-(const Vector3<T>& v) {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline Vector3<T> operator*(float f) {
        return Vector3<T>(x * f, y * f, z * f);
    }

    inline T& operator[](int i) {
        return raw[i];
    }

    inline Vector3<T>& operator=(const Vector3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    inline float length() const {
        return sqrt(raw[0] * raw[0] + raw[1] * raw[1] + raw[2] * raw[2]);
    }

    inline Vector3<T>& normalize() {
        *this = (*this) * (1 / length());
        return *this;
    }
};

template<typename T>
inline float dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

template<typename T>
inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>((v1.y * v2.z - v1.z * v2.y),
                (-(v1.x * v2.z - v1.z * v2.x)),
                (v1.x * v2.y - v1.y * v2.x));
}
