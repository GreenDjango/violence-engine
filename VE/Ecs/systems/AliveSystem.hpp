/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** AliveSystem
*/

#ifndef ALIVESYSTEM_HPP_
#define ALIVESYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/basic.hpp"
#include "VE/Ecs/components/AliveZone.hpp"
#include <vector>

namespace ve {

class AliveSystem : public ecs::System {
public:
    void Update(Coordinator &ecs) {
        std::vector<ecs::Entity> deleteQueue;
        for (auto entity : ecs::System::entites) {
            auto &alive = ecs.getComponent<AliveZone>(entity);
            auto &transform = ecs.getComponent<Transform>(entity);

            if (transform.pos.x < alive.zone.x ||
                transform.pos.y < alive.zone.y ||
                transform.pos.x > alive.zone.x + alive.zone.sx ||
                transform.pos.y > alive.zone.y + alive.zone.sy) {
                deleteQueue.push_back(entity);
            }
        }
        for (auto entity : deleteQueue)
            ecs.destroyEntity(entity);
    }

    static std::shared_ptr<AliveSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<AliveZone>();
        ecs.registerComponentIfNotExist<Transform>();

        auto aliveSystem = ecs.registerSystem<AliveSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<AliveZone>());
            signature.set(ecs.getComponentType<Transform>());
            ecs.setSystemSignature<AliveSystem>(signature);
        }
        return aliveSystem;
    }
};

} // namespace ve

#endif /* !ALIVESYSTEM_HPP_ */