/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** AnimatorSystem
*/

#ifndef ANIMATORSYSTEM_HPP_
#define ANIMATORSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Animation.hpp"
#include "VE/Ecs/components/Sprite.hpp"

namespace ve {

class AnimatorSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float deltaTime) {
        for (auto entity : ecs::System::entites) {
            auto &render = ecs.getComponent<Sprite>(entity);
            auto &animation = ecs.getComponent<Animation>(entity);
            auto oldIndex = animation.frameIndex;

            animation.msElapsed += deltaTime * 1000;

            if (animation.msByFrame > 0 && animation.msElapsed >= animation.msByFrame) {
                int skipFrame = animation.msElapsed / animation.msByFrame;
                int maxLength = animation.xSize * animation.ySize;
                animation.msElapsed -= animation.msByFrame * skipFrame;

                int frame = animation.frameIndex + ((animation.foreward) ? skipFrame : -skipFrame);
                if (animation.loop || (frame < maxLength && frame >= 0)) {
                    if (frame < 0)
                        animation.frameIndex = maxLength - (-frame % maxLength);
                    else
                        animation.frameIndex = frame % maxLength;
                } else {
                    if (frame >= maxLength)
                        animation.frameIndex = maxLength - 1;
                    else
                        animation.frameIndex = 0;
                }
            }

            if (oldIndex != animation.frameIndex || animation.firstRender) {
                int y = animation.frameIndex / animation.xSize;
                int x = animation.frameIndex % animation.xSize;
                render.sprite.setTextureRect({ x * (int)animation.frameWidth, y * (int)animation.frameHeight, (int)animation.frameWidth, (int)animation.frameHeight });
                animation.firstRender = false;
            }
        }
    }

    static std::shared_ptr<AnimatorSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Sprite>();
        ecs.registerComponentIfNotExist<Animation>();

        auto animatorSystem = ecs.registerSystem<AnimatorSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Sprite>());
            signature.set(ecs.getComponentType<Animation>());
            ecs.setSystemSignature<AnimatorSystem>(signature);
        }
        return animatorSystem;
    }
};

} // namespace ve

#endif /* !ANIMATORSYSTEM_HPP_ */
