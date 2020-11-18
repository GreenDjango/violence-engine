/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** UiSystem
*/

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Sprite.hpp"
#include "VE/Ecs/components/Text.hpp"
#include "VE/Ecs/components/Transform.hpp"
#include "VE/Ecs/components/UiTrigger.hpp"

namespace ve {

class UiSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float, const Size &win = { 1920, 1080 }) {
        for (auto entity : ecs::System::entites) {
            auto &transform = ecs.getComponent<Transform>(entity);
            auto &ui = ecs.getComponent<UiTrigger>(entity);

            Size boxSize = win;
            if (ui.sub.sx > 1)
                boxSize.sx /= ui.sub.sx;
            if (ui.sub.sy > 1)
                boxSize.sy /= ui.sub.sy;
            Size boxOff(boxSize.sx * ui.pos.sx, boxSize.sy * ui.pos.sy);

            sf::FloatRect bounds;
            if (ecs.hasComponent<Sprite>(entity))
                bounds = ecs.getComponent<Sprite>(entity).sprite.getLocalBounds();
            if (ecs.hasComponent<Text>(entity))
                bounds = ecs.getComponent<Text>(entity)._text.getLocalBounds();
            bounds.width *= transform.scale.x;
            bounds.height *= transform.scale.y;
            Vec2d pos;

            if (ui.align & AlignFlag::FlagRight) {
                pos.x = boxSize.sx - bounds.width;
            } else if (ui.align & AlignFlag::FlagHCenter) {
                pos.x = boxSize.sx / 2 - bounds.width / 2;
            } else {
                // pos.x == 0 by default
            }
            if (ui.align & AlignFlag::FlagBottom) {
                pos.y = boxSize.sy - bounds.height;
            } else if (ui.align & AlignFlag::FlagVCenter) {
                pos.y = boxSize.sy / 2 - bounds.height / 2;
            } else {
                // pos.y == 0 by default
            }
            transform.pos.x = (int)(pos.x + boxOff.sx);
            transform.pos.y = (int)(pos.y + boxOff.sy);
        }
    }

    static std::shared_ptr<UiSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Transform>();
        ecs.registerComponentIfNotExist<UiTrigger>();
        ecs.registerComponentIfNotExist<Sprite>();
        ecs.registerComponentIfNotExist<Text>();

        auto uiSystem = ecs.registerSystem<UiSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Transform>());
            signature.set(ecs.getComponentType<UiTrigger>());
            ecs.setSystemSignature<UiSystem>(signature);
        }
        return uiSystem;
    }
};

} // namespace ve

#endif /* !UISYSTEM_HPP_ */
