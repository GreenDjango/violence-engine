/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** TimeEventSystem
*/

#ifndef TIMEEVENTSYSTEM_HPP_
#define TIMEEVENTSYSTEM_HPP_

#include "VE/Core/managers/WindowManager.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Life.hpp"
#include "VE/Ecs/components/RigidBody.hpp"
#include "VE/Ecs/components/Sprite.hpp"
#include "VE/Ecs/components/TimeEvent.hpp"
#include "VE/Ecs/components/Transform.hpp"

namespace ve {

class TimeSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float delta) {
        unsigned int deltaMs = ((unsigned int)(delta * 1000));
        for (auto entity : ecs::System::entites) {
            auto &time = ecs.getComponent<TimeEvent>(entity);

            for (auto &e2 : time.events) {
                EventCall &event = e2.second;
                if (event.enable) {
                    event.elapsed += deltaMs;
                    if (event.elapsed > event.delay) {
                        event.elapsed = 0;
                        event.func(ecs, entity);
                    }
                }
            }
        }
    }

    static std::shared_ptr<TimeSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<TimeEvent>();

        auto renderSystem = ecs.registerSystem<TimeSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<TimeEvent>());
            ecs.setSystemSignature<TimeSystem>(signature);
        }
        return renderSystem;
    }
};

} // namespace ve

#endif /* !TIMEEVENTSYSTEM_HPP_ */
