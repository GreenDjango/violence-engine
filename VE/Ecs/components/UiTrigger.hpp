/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** UiTrigger
*/

#ifndef UITRIGGER_HPP_
#define UITRIGGER_HPP_

#include "VE/Maths/Size.hpp"
// #include "VE/Maths/Vec2d.hpp"
#include "VE/Utils/align.hpp"

// sub screen:
// subX(4) subY(3) posX(2) posY(1)
// ┌───────────┐
// |  |  |  |  |
// ├-----------┤
// |  |  |xx|  |
// ├-----------┤
// |  |  |  |  |
// └───────────┘

namespace ve {

struct UiTrigger {
    // Vec2d start;
    Align align;
    Size sub;
    Size pos;

    UiTrigger()
        : align(Align::LeftTop) {}

    UiTrigger(Align align, Size sub = { 0 }, Size pos = { 0 })
        : align(align), sub(sub), pos(pos) {}

    static UiTrigger create(Align align = Align::LeftTop, Size sub = { 0 }, Size pos = { 0 }) {
        return { align, sub, pos };
    }
};

} // namespace ve

#endif /* !UITRIGGER_HPP_ */