/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Life
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

namespace ve {

#include "VE/Maths/Rect.hpp"

struct Life {
    float life;
    float maxLife;
    bool bar;
    Rect relative;
};

} // namespace ve

#endif /* !LIFE_HPP_ */
