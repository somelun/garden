#pragma once

#include <iostream>
#include "vec.h"

using mat4_t = int;

class mat4 {
public:

    mat4_t& at(int row, int column);
    const mat4_t& at(int row, int column) const;

    mat4 operator*(const mat4& m);
    vec4f operator*(const vec4f& v);

    mat4 transpose();
    // mat4 inverse();  //TODO

    friend std::ostream& operator<<(std::ostream& s, mat4& m);

private:
    mat4_t data_[16] = {0};
};

static mat4 mat4_identity() {
    mat4 m;
    m.at(0, 0) = m.at(1, 1) = m.at(2, 2) = m.at(3, 3) = 1.0f;
    return m;
}

// static mat4 mat4_test() {
//     mat4 m;
//     int t = 0;
//     for (int i = 0; i < 4; ++i) {
//         for (int j = 0; j < 4; ++j) {
//             m.at(i, j) = ++t;
//         }
//     }
//     return m;
// }
