/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** RigidBody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include "VE/Maths/Vec2d.hpp"
#include <functional>
#include <float.h>
#include <set>

namespace ve {

using CallBack = std::function<void(Coordinator &ecs, ecs::Entity, ecs::Entity, std::set<ecs::Entity> &)>;

struct RigidBody {

    Vec2d pos;
    Vec2d width;
    Vec2d velocity;
    float angularVelocity;

    Vec2d force;
    float torque;

    float friction;
    float mass;
    float invMass;
    float I;
    float invI;

    CallBack onCollision;

    RigidBody() {
        friction = 0.2f;
        mass = FLT_MAX;
        I = FLT_MAX;
    }

    static RigidBody create(const Vec2d width, float massBody, const Vec2d pos = { 0 }, CallBack onCollision = nullptr) {
        RigidBody body{};
        body.set(width, massBody);
        body.pos = pos;
        body.onCollision = onCollision;
        return body;
    }

    static float constexpr STATIC_BODY = FLT_MAX;

    void set(const Vec2d &widthXY, float massBody) {
        friction = 0.2f;
        width = widthXY;
        mass = massBody;

        if (mass < FLT_MAX) {
            invMass = 1.0f / mass;
            I = mass * (width.x * width.x + width.y * width.y) / 12.0f;
            invI = 1.0f / I;
        } else {
            invMass = 0.0f;
            I = FLT_MAX;
            invI = 0.0f;
        }
    }

    void addForce(const Vec2d &f) {
        force += f;
    }
};

} // namespace ve

#endif /* !RIGIDBODY_HPP_ */