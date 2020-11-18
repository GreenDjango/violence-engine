/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Mat22
*/

#ifndef MAT22_HPP_
#define MAT22_HPP_

#include "VE/Maths/Vec2d.hpp"
#include <cassert>
#include <cmath>

namespace ve {

struct Mat22 {
    Mat22() {}

    Mat22(float angle) {
        float c = std::cos(angle);
        float s = std::sin(angle);
        col1.x = c;
        col2.x = -s;
        col1.y = s;
        col2.y = c;
    }

    Mat22(const Vec2d &col1, const Vec2d &col2) : col1(col1), col2(col2) {}

    Mat22 transpose() const {
        return Mat22(Vec2d(col1.x, col2.x), Vec2d(col1.y, col2.y));
    }

    Mat22 invert() const {
        float a = col1.x, b = col2.x, c = col1.y, d = col2.y;
        Mat22 B;
        float det = a * d - b * c;
        assert(det != 0.0f);
        det = 1.0f / det;
        B.col1.x = det * d;
        B.col2.x = -det * b;
        B.col1.y = -det * c;
        B.col2.y = det * a;
        return B;
    }

    Mat22 abs() const {
        return Mat22(col1.abs(), col2.abs());
    }

    Vec2d operator*(const Vec2d &v) const {
        return Vec2d(col1.x * v.x + col2.x * v.y, col1.y * v.x + col2.y * v.y);
    }

    Mat22 operator*(const Mat22 &m) const {
        return Mat22(*this * m.col1, *this * m.col2);
    }

    Vec2d col1, col2;
};

} // namespace ve

#endif /* !MAT22_HPP_ */