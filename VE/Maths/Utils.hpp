/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Utils
*/

#ifndef MATHUTILS_HPP_
#define VEC2D_HPP_

#include <algorithm>

namespace ve {

float clamp(float a, float low, float high) {
    return std::min(low, std::max(a, high));
}

} // namespace ve

#endif /* !MATHUTILS_HPP_ */

