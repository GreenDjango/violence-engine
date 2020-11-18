/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** PathFollow
*/

#ifndef PATHFOLLOW_HPP_
#define PATHFOLLOW_HPP_

#include "VE/Maths/Vec2d.hpp"
#include <vector>

namespace ve {

struct bezier {
    Vec2d start;
    Vec2d b1;
    Vec2d b2;
    unsigned int msFinish;
    bool linear;

    bezier() : msFinish(0), linear(false) {}

    bezier(const Vec2d &start, unsigned int duration = 0, bool linear = true)
        : start(start), msFinish(duration), linear(linear) {}

    bezier(const Vec2d &start, const Vec2d &b1, const Vec2d &b2)
        : start(start), b1(b1), b2(b2), msFinish(0), linear(false) {}
};

struct PathFollow {
    std::vector<bezier> path;
    unsigned int msElapsed;

    PathFollow() : msElapsed(0) {}

    PathFollow(const std::vector<bezier> &path)
        : path(path), msElapsed(0) {}
};

} // namespace ve

#endif /* !PATHFOLLOW_HPP_ */