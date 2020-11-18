/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** vec3d
*/

#ifndef VEC3D_HPP_
#define VEC3D_HPP_

namespace ve {

class Vec3d {
public:
    float x;
    float y;
    float z;

    Vec3d()
        : x{ 0 }, y{ 0 }, z{ 0 } {
    }

    Vec3d(float n)
        : x{ n }, y{ n }, z{ n } {
    }

    Vec3d(float nx, float ny, float nz)
        : x{ nx }, y{ ny }, z{ nz } {
    }

    Vec3d operator+=(Vec3d const &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3d operator+=(Vec2d const &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec3d operator*(float factor) const {
        return Vec3d(
            x * factor,
            y * factor,
            z * factor);
    }
};

} // namespace ve

#endif /* !VEC3D_HPP_ */
