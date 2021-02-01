#include "mat.h"


mat4 mat4::operator*(const mat4& m) {
    mat4 result;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            for (size_t k = 0; k < 4; ++k) {
                result.at(i, j) += data_[i * 4 + k] * m.at(k, j);
            }
        }
    }
    return result;
}

mat4_t& mat4::at(int row, int column) {
    return data_[row * 4 + column];
}

const mat4_t& mat4::at(int row, int column) const {
    return data_[row * 4 + column];
}

std::ostream& operator<<(std::ostream& s, mat4& m) {
    for (size_t i = 0; i < 16; i = i + 4) {
        s << m.data_[i] << " "
          << m.data_[i + 1] << " "
          << m.data_[i + 2] << " "
          << m.data_[i + 3] << "\n"
          ;
    }
    return s;
}
