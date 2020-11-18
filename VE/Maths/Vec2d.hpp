/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Vec2d
*/

#ifndef VEC2D_HPP_
#define VEC2D_HPP_

#include <cmath>

namespace ve {

class Vec2d {
public:
    float x;
    float y;

    Vec2d()
        : x{ 0 }, y{ 0 } {
    }

    Vec2d(float n)
        : x{ n }, y{ n } {
    }

    Vec2d(float nx, float ny)
        : x{ nx }, y{ ny } {
    }

    Vec2d abs() const {
        return Vec2d(
            std::abs(x),
            std::abs(y));
    }

    float dot(const Vec2d &b) const {
        return x * b.x + y * b.y;
    }

    float cross(const Vec2d &b) const {
        return x * b.y - y * b.x;
    }

    Vec2d cross(float s) const {
        return Vec2d(s * y, -s * x);
    }

    Vec2d operator-() const {
        return Vec2d(-x, -y);
    }

    Vec2d operator-(Vec2d const &other) const {
        return Vec2d(
            x - other.x,
            y - other.y);
    }

    Vec2d operator-=(Vec2d const &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2d operator+(Vec2d const &other) const {
        return Vec2d(
            x + other.x,
            y + other.y);
    }

    Vec2d operator+=(Vec2d const &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2d operator*(float factor) const {
        return Vec2d(
            x * factor,
            y * factor);
    }

    Vec2d operator*(Vec2d const &other) const {
        return Vec2d(
            x * other.x,
            y * other.y);
    }

    Vec2d operator*=(float factor) {
        x *= factor;
        y *= factor;
        return *this;
    }

    bool operator==(Vec2d const &other) const {
        return x == other.x && y == other.y;
    }
};

} // namespace ve

#endif /* !VEC2D_HPP_ */
