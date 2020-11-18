/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Contact
*/

#ifndef CONTACT_HPP_
#define CONTACT_HPP_

#include "VE/Maths/Vec2d.hpp"

namespace ve {

union FeaturePair {
    struct Edges {
        char inEdge1;
        char outEdge1;
        char inEdge2;
        char outEdge2;
    } e;
    int value;
};

struct Contact {
    Contact() : Pn(0.0f), Pt(0.0f), Pnb(0.0f) {}

    Vec2d position;
    Vec2d normal;
    Vec2d r1, r2;
    float separation;
    float Pn;  // accumulated normal impulse
    float Pt;  // accumulated tangent impulse
    float Pnb; // accumulated normal impulse for position bias
    float massNormal, massTangent;
    float bias;
    FeaturePair feature;
};

} // namespace ve

#endif /* !CONTACT_HPP_ */
