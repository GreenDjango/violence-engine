/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** TransitionSystem
*/

#ifndef TRANSITIONSYSTEM_HPP_
#define TRANSITIONSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Sprite.hpp"
#include "VE/Ecs/components/Transition.hpp"
namespace ve {

class TransitionSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float deltaTime) {
        for (auto entity : ecs::System::entites) {
            auto &render = ecs.getComponent<Sprite>(entity);
            auto &transition = ecs.getComponent<Transition>(entity);

            if (transition.msElapsed >= transition.duration)
                continue;
            transition.msElapsed += deltaTime * 1000;
            if (transition.msElapsed > transition.duration)
                transition.msElapsed = transition.duration;

            float ratio = (float)transition.msElapsed / (float)transition.duration;
            unsigned char alpha = transition.sFade.a() + ((float)(transition.eFade.a()) - (float)(transition.sFade.a())) * ratio;
            auto color = render.sprite.getColor();
            color.a = alpha;
            render.sprite.setColor(color);
        }
    }

    static std::shared_ptr<TransitionSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Sprite>();
        ecs.registerComponentIfNotExist<Transition>();

        auto transitionSystem = ecs.registerSystem<TransitionSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Sprite>());
            signature.set(ecs.getComponentType<Transition>());
            ecs.setSystemSignature<TransitionSystem>(signature);
        }
        return transitionSystem;
    }
};

} // namespace ve

#endif /* !TRANSITIONSYSTEM_HPP_ */
