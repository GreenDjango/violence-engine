/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** PhysicsSystem
*/

#ifndef PHYSICSSYSTEM_HPP_
#define PHYSICSSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/MaxSpeed.hpp"
#include "VE/Ecs/components/Motion.hpp"
#include "VE/Ecs/components/Transform.hpp"
#include "VE/Ecs/components/StreamPosition.hpp"
#include <SFML/Graphics.hpp>

namespace ve {

class PhysicsSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float deltaTime) {
        for (auto entity : ecs::System::entites) {
            auto &motion = ecs.getComponent<Motion>(entity);
            auto &transform = ecs.getComponent<Transform>(entity);

            motion.speed += motion.gravity * deltaTime;
            if (ecs.hasComponent<MaxSpeed>(entity)) {
                auto &maxSpeed = ecs.getComponent<MaxSpeed>(entity);
                if (motion.speed.x > maxSpeed.max.x)
                    motion.speed.x = maxSpeed.max.x;
                else if (motion.speed.x < -maxSpeed.max.x)
                    motion.speed.x = -maxSpeed.max.x;
                if (motion.speed.y > maxSpeed.max.y)
                    motion.speed.y = maxSpeed.max.y;
                else if (motion.speed.y < -maxSpeed.max.y)
                    motion.speed.y = -maxSpeed.max.y;
            }
            transform.pos += motion.speed * deltaTime;
            if (ecs.hasComponent<StreamPosition>(entity)) {
                // Stream me
                // transform.pos;
            }
        }
    }

    static std::shared_ptr<PhysicsSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Motion>();
        ecs.registerComponentIfNotExist<Transform>();
        ecs.registerComponentIfNotExist<MaxSpeed>();
        ecs.registerComponentIfNotExist<StreamPosition>();

        auto physicsSystem = ecs.registerSystem<PhysicsSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Motion>());
            signature.set(ecs.getComponentType<Transform>());
            ecs.setSystemSignature<PhysicsSystem>(signature);
        }
        return physicsSystem;
    }
};

} // namespace ve

#endif /* !PHYSICSSYSTEM_HPP_ */
