/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "VE/Maths/Vec3d.hpp"
#include "VE/Maths/Vec2d.hpp"

namespace ve {

struct Transform {
    Vec3d pos;
    float rot;
    Vec2d scale;
    Vec2d flip;
};

} // namespace ve

#endif /* !TRANSFORM_HPP_ */
