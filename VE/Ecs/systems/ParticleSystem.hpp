/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include "VE/Core/managers/WindowManager.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Emitter.hpp"
#include "VE/Ecs/components/Transform.hpp"

namespace ve {

class ParticleSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, float deltaTime) {
        for (auto entity : ecs::System::entites) {
            auto &emitter = ecs.getComponent<Emitter>(entity);

            for (auto &particle : emitter.particles) {
                particle.timeLeft -= deltaTime;
                if (particle.timeLeft <= 0) {
                    auto &trans = ecs.getComponent<Transform>(entity).pos;
                    particle.timeLeft = particle.lifeTime;
                    particle.scale = particle.startScale;
                    if (emitter.region)
                        particle.pos = emitter.region->getPoint({ trans.x, trans.y });
                    else
                        particle.pos = { trans.x, trans.y };
                }

                particle.scale += particle.scaleSpeed * deltaTime;

                particle.pos += particle.velocity * deltaTime;
            }
        }
    }

    void Update(Coordinator &ecs, WindowManager *window) {
        for (auto entity : ecs::System::entites) {
            auto &emitter = ecs.getComponent<Emitter>(entity);

            RectShape rectShape(4, 4);
            Shape *shape;
            if (emitter.shape) {
                shape = emitter.shape.get();
            } else {
                shape = &rectShape;
            }

            for (auto &particle : emitter.particles) {
                shape->setPosition(particle.pos);
                shape->setScale(particle.scale);

                float ratio = particle.timeLeft / particle.lifeTime;
                float fadeStart = 1.f - particle.fadePercent / 100.f;
                if (fadeStart < ratio)
                    ratio = 1;
                else
                    ratio = particle.timeLeft / (particle.lifeTime * fadeStart);

                auto col1 = shape->getFillColor();
                auto col2 = shape->getOutlineColor();
                col1.setA((unsigned char)(ratio * 255));
                col2.setA((unsigned char)(ratio * 255));
                shape->setFillColor(col1);
                shape->setOutlineColor(col2);

                window->draw(shape->getShape());
            }
        }
    }

    static std::shared_ptr<ParticleSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Transform>();
        ecs.registerComponentIfNotExist<Emitter>();

        auto particleSystem = ecs.registerSystem<ParticleSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Transform>());
            signature.set(ecs.getComponentType<Emitter>());
            ecs.setSystemSignature<ParticleSystem>(signature);
        }
        return particleSystem;
    }
};

} // namespace ve

#endif /* !PARTICLESYSTEM_HPP_ */
