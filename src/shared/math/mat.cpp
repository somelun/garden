#include "mat.h"


// mat4::mat4(mat_t a00, mat_t a01, mat_t a02, mat_t a03,
//            mat_t a10, mat_t a11, mat_t a12, mat_t a13,
//            mat_t a20, mat_t a21, mat_t a22, mat_t a23,
//            mat_t a30, mat_t a31, mat_t a32, mat_t a33) {
// 
//     data_[0] = a00;
//     data_[1] = a01;
//     data_[2] = a02;
//     data_[3] = a03;
//     data_[4] = a10;
//     data_[5] = a11;
//     data_[6] = a12;
//     data_[7] = a13;
//     data_[8] = a20;
//     data_[9] = a21;
//     data_[10] = a22;
//     data_[11] = a23;
//     data_[12] = a30;
//     data_[13] = a31;
//     data_[14] = a32;
//     data_[15] = a33;
// }
// 
// mat4 mat4::operator*(const mat4& m) const {
//     mat4 result = {};
// 
//     for (size_t i = 0; i < 4; ++i) {
//         for (size_t k = 0; k < 4; ++k) {
//             for (size_t j = 0; j < 4; ++j) {
//                 result.at(i, j) += data_[i * 4 + k] * m.at(k, j);
//             }
//         }
//     }
// 
//     return result;
// }
// 
// vec4f mat4::operator*(const vec4f& v) const {
//     vec4f result = {};
// 
//     for (size_t i = 0; i < 4; ++i) {
//         for (size_t j = 0; j < 4; ++j) {
//             result[i] += data_[i * 4 + j] * v[j];
//         }
//     }
// 
//     return {result.x / result.w, result.y / result.w, result.z / result.w, result.w / result.w};
// }
// 
// vec3f mat4::operator*(const vec3f& v) const {
//     vec4f result = {};
//     vec4f v4 = {v, 1.0f};
// 
//     for (size_t i = 0; i < 4 ; ++i) {
//         for (size_t j = 0; j < 4; ++j) {
//             result[i] += data_[i * 4 + j] * v4[j];
//         }
//     }
// 
//     return {result.x / result.w, result.y / result.w, result.z / result.w};
// }
// 
// mat_t& mat4::at(int row, int column) {
//     return data_[row * 4 + column];
// }
// 
// const mat_t& mat4::at(int row, int column) const {
//     return data_[row * 4 + column];
// }
// 
// mat4 mat4::transpose() {
//     mat4 result = {};
// 
//     for (size_t i = 0; i < 4; ++i) {
//         for (size_t j = 0; j < 4; ++j) {
//             result.at(i, j) = data_[j * 4 + i];
//         }
//     }
// 
//     return result;
// }
// 
// mat4 mat4::inverse() {
//     mat4 adj = adjoint();
//     float det = 0.0f;
// 
//     for (size_t i = 0; i < 4; ++i) {
//         det += data_[i] * adj.at(0, i);
//     }
// 
//     det = 1.0f / det;
//     mat4 inverse_transpose = {};
// 
//     for (size_t i = 0; i < 4; ++i) {
//         for (size_t j = 0; j < 4; ++j) {
//             inverse_transpose.at(i, j) = adj.at(i, j) * det;
//         }
//     }
// 
//     return adj.transpose();
// }
// 
// mat4 mat4::adjoint() {
//     mat4 adj = {};
// 
//     for (size_t i = 0; i < 4; ++i) {
//         for (size_t j = 0; j < 4; ++j) {
//             adj.at(i, j) = cofactor(i, j);
//         }
//     }
// 
//     return adj;
// }
// 
// mat_t mat4::cofactor(size_t r, size_t c) {
//     float sign = (r + c) % 2 == 0 ? 1.0f : -1.0f;
//     mat_t m = minor(r, c);
//     return sign * m;
// }
// 
// mat_t mat4::minor(size_t r, size_t c) {
//     mat3 m = {};
// 
//     for (size_t i = 0; i < 3; ++i) {
//         for (size_t j = 0; j < 3; ++j) {
//             size_t row = i < r ? i : i + 1;
//             size_t column = j < c ? j : j + 1;
//             m.data_[i * 3 + j] = this->at(row, column);
//         }
//     }
// 
//     return m.determinant();
// }
// 
// mat_t mat3::determinant() {
//     return data_[0] * (data_[4] * data_[8] - data_[5] * data_[7])
//          - data_[1] * (data_[3] * data_[8] - data_[5] * data_[6])
//          + data_[2] * (data_[3] * data_[7] - data_[4] * data_[6]);
// }
// 
// std::ostream& operator<<(std::ostream& s, const mat4& m) {
//     for (size_t i = 0; i < 16; i = i + 4) {
//         s << m.data_[i] << " "
//           << m.data_[i + 1] << " "
//           << m.data_[i + 2] << " "
//           << m.data_[i + 3] << "\n"
//           ;
//     }
// 
//     return s;
// }
// 
// std::ostream& operator<<(std::ostream& s, const mat3& m) {
//     for (size_t i = 0; i < 9; i = i + 3) {
//         s << m.data_[i] << " "
//           << m.data_[i + 1] << " "
//           << m.data_[i + 2] << "\n"
//           ;
//     }
// 
//     return s;
// }
