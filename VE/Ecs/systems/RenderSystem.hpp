/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "VE/Core/managers/WindowManager.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/components/FxShader.hpp"
#include "VE/Ecs/components/RigidBody.hpp"
#include "VE/Ecs/components/Sprite.hpp"
#include "VE/Ecs/components/Text.hpp"
#include "VE/Ecs/components/Transform.hpp"
#include "VE/Utils/random.hpp"

namespace ve {

class RenderSystem : public ecs::System {
public:
    void updateZIndex(Coordinator &ecs) {
        struct sortFucntion {
            sortFucntion(Coordinator &ecs) : _ecs{ ecs } {}
            bool operator()(ecs::Entity a, ecs::Entity b) const {
                return _ecs.getComponent<Transform>(a).pos.z < _ecs.getComponent<Transform>(b).pos.z;
            }
            ve::Coordinator &_ecs;
        };
        entites.sort(sortFucntion(ecs));
    }

    void Update(Coordinator &ecs, WindowManager *window) {
        timer += 1;
        for (auto entity : ecs::System::entites) {
            auto &render = ecs.getComponent<Sprite>(entity);
            auto &transform = ecs.getComponent<Transform>(entity);
            render.sprite.setPosition(transform.pos.x, transform.pos.y);
            render.sprite.setScale(transform.scale.x, transform.scale.y);
            render.sprite.setRotation(transform.rot);

            if (transform.flip.x) {
                render.sprite.scale(-1, 1);
                render.sprite.move({ render.sprite.getGlobalBounds().width, 0 });
            }
            if (ecs.hasComponent<FxShader>(entity) && ecs.getComponent<FxShader>(entity).enable) {
                auto &fx = ecs.getComponent<FxShader>(entity);
                sf::RenderTexture renderText;
                renderText.create(1920, 1080);
                renderText.clear(sf::Color::Transparent);
                renderText.draw(render.sprite);
                renderText.display();
                if (fx.timer)
                    fx.shader.setUniform("timer", timer);
                if (fx.intensity)
                    fx.shader.setUniform("intensity", fx.intensityVal);
                if (fx.rand)
                    fx.shader.setUniform("rand", (float)randInt(0, 100) / 100.f);
                sf::Sprite sprite(renderText.getTexture());
                window->draw(sprite, &(fx.shader.getShader()));
            } else {
                window->draw(render.sprite);
            }

            if (ecs.hasComponent<Text>(entity)) {
                auto &text = ecs.getComponent<Text>(entity);
                text._text.setPosition(transform.pos.x, transform.pos.y);
                text._text.setScale(transform.scale.x, transform.scale.y);
                text._text.setRotation(transform.rot);

                if (transform.flip.x) {
                    text._text.scale(-1, 1);
                    text._text.move({ text._text.getGlobalBounds().width, 0 });
                }
                window->draw(text._text);
            }

            // if (ecs.hasComponent<RigidBody>(entity)) {
            //     auto &body = ecs.getComponent<RigidBody>(entity);
            //     sf::RectangleShape rectangle(sf::Vector2f(body.width.x, body.width.y));
            //     rectangle.setPosition(transform.pos.x + body.pos.x, transform.pos.y + body.pos.y);
            //     rectangle.setOutlineThickness(2);
            //     rectangle.setOutlineColor({ 200, 0, 0 });
            //     rectangle.setFillColor({ 200, 0, 0, 100 });
            //     window->draw(rectangle);
            // }
        }
    }

    static std::shared_ptr<RenderSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Sprite>();
        ecs.registerComponentIfNotExist<Text>();
        ecs.registerComponentIfNotExist<RigidBody>();
        ecs.registerComponentIfNotExist<FxShader>();
        ecs.registerComponentIfNotExist<Transform>();

        auto renderSystem = ecs.registerSystem<RenderSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Sprite>());
            signature.set(ecs.getComponentType<Transform>());
            ecs.setSystemSignature<RenderSystem>(signature);
        }
        renderSystem->timer = 0;
        return renderSystem;
    }

    float timer;
};

} // namespace ve

#endif /* !RENDERSYSTEM_HPP_ */
