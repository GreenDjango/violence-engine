/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** PathSystem
*/

#ifndef PATHSYSTEM_HPP_
#define PATHSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/PathFollow.hpp"
#include "VE/Ecs/components/Transform.hpp"
#include <array>
#include <iostream>
#include <math.h>

namespace ve {

class PathSystem : public ecs::System {
public:
    // P = (1−t)^3P1 + 3(1−t)^2tP2 + 3(1−t)t^2P3 + t^3P4
    static Vec2d getBezierPoint(const Vec2d &start, const Vec2d &b1, const Vec2d &b2, const Vec2d &end, float t) {
        Vec2d pos = (start * std::pow(1 - t, 3)) + (b1 * (3 * t * (std::pow(1 - t, 2)))) + (b2 * (3 * std::pow(t, 2) * (1 - t))) + (end * std::pow(t, 3));
        return pos;
    }

    void lisseSpeed(Coordinator &ecs, float speedPixelSec, int precision) {
        for (auto &entity : ecs::System::entites) {
            auto &pf = ecs.getComponent<PathFollow>(entity);
            for (size_t i = 0; i < pf.path.size() - 1; i++) {
                if (pf.path[i].msFinish > 0) continue;
                double dist = 0;
                Vec2d old = pf.path[i].start;
                for (int a = 1; a < precision; a++) {
                    auto vec = getBezierPoint(
                        pf.path[i].start,
                        pf.path[i].b1,
                        pf.path[i].b2,
                        pf.path[i + 1].start,
                        (float)a / (float)precision);
                    dist += std::sqrt(std::pow(old.x - vec.x, 2) + std::pow(old.y - vec.y, 2));
                    old = vec;
                }
                float t = (dist / speedPixelSec) * 1000;
                pf.path[i].msFinish = (unsigned int)(t);
            }
        }
    }

    void Update(Coordinator &ecs, float deltaTime) {
        for (auto entity : ecs::System::entites) {
            auto &transfrom = ecs.getComponent<Transform>(entity);
            auto &pathFollow = ecs.getComponent<PathFollow>(entity);

            pathFollow.msElapsed += (deltaTime * 1000);
            auto remainTime = pathFollow.msElapsed;
            size_t index = 0;
            for (; index < pathFollow.path.size() && remainTime > pathFollow.path[index].msFinish; index++)
                remainTime -= pathFollow.path[index].msFinish;
            if (index + 1 >= pathFollow.path.size()) {
                pathFollow.msElapsed = 0;
                continue;
            }
            Vec2d vec;
            float t = (float)remainTime / (float)pathFollow.path[index].msFinish;
            if (pathFollow.path[index].linear)
                vec = pathFollow.path[index].start * (1 - t) + pathFollow.path[index + 1].start * t;
            else
                vec = getBezierPoint(
                    pathFollow.path[index].start,
                    pathFollow.path[index].b1,
                    pathFollow.path[index].b2,
                    pathFollow.path[index + 1].start,
                    t);
            transfrom.pos.x = vec.x;
            transfrom.pos.y = vec.y;
        }
    }

    static std::shared_ptr<PathSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Transform>();
        ecs.registerComponentIfNotExist<PathFollow>();

        auto physicsSystem = ecs.registerSystem<PathSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Transform>());
            signature.set(ecs.getComponentType<PathFollow>());
            ecs.setSystemSignature<PathSystem>(signature);
        }
        return physicsSystem;
    }
};

} // namespace ve

#endif /* !PATHSYSTEM_HPP_ */
