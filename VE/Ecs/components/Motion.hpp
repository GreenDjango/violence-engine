/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Motion
*/

#ifndef MOTION_HPP_
#define MOTION_HPP_

#include "VE/Maths/Vec2d.hpp"

namespace ve {

struct Motion {
    Vec2d speed;
    Vec2d gravity;
};

} // namespace ve

#endif /* !MOTION_HPP_ */
