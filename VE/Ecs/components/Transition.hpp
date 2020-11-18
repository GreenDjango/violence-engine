/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Transition
*/

#ifndef TRANSITION_HPP_
#define TRANSITION_HPP_

#include "VE/Core/classes/Color.hpp"

namespace ve {

struct Transition {
    Color sFade;
    Color eFade;
    unsigned int duration;
    bool loop;
    bool foreward;
    unsigned int msElapsed;
    bool pause;

    Transition()
        : sFade(255, 255), eFade(255, 255), duration(1000), loop(false), foreward(true), msElapsed(0), pause(false) {}

    Transition(const Color sFade, const Color eFade, unsigned int duration, bool loop, bool foreward)
        : sFade(sFade), eFade(eFade), duration(duration), loop(loop), foreward(foreward), msElapsed(0), pause(false) {}

    static Transition create(const Color sFade, const Color eFade, unsigned int duration, bool loop = false, bool foreward = true) {
        return Transition{ sFade, eFade, duration, loop, foreward };
    }
};

} // namespace ve

#endif /* !TRANSITION_HPP_ */