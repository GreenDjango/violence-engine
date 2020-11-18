/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** LifeSystem
*/

#ifndef LIFESYSTEM_HPP_
#define LIFESYSTEM_HPP_

#include "VE/Core/managers/WindowManager.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Life.hpp"
#include "VE/Ecs/components/RigidBody.hpp"
#include "VE/Ecs/components/Sprite.hpp"
#include "VE/Ecs/components/Transform.hpp"

namespace ve {

class LifeSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, WindowManager *window) {
        for (auto entity : ecs::System::entites) {
            auto &life = ecs.getComponent<Life>(entity);
            if (!life.bar)
                continue;
            auto &transform = ecs.getComponent<Transform>(entity);

            float ratio = life.life / life.maxLife;

            sf::RectangleShape backRect(sf::Vector2f(life.relative.sx, life.relative.sy));
            backRect.setPosition(transform.pos.x + life.relative.x, transform.pos.y + life.relative.y);
            backRect.setFillColor({ 0, 0, 0, 170 });

            sf::RectangleShape lifeRect(sf::Vector2f((float)life.relative.sx * ratio, life.relative.sy));
            lifeRect.setPosition((int)transform.pos.x + life.relative.x, (int)transform.pos.y + life.relative.y);
            if (ratio > 0.5)
                lifeRect.setFillColor(sf::Color::Green);
            else if (ratio > 0.25)
                lifeRect.setFillColor(sf::Color::Yellow);
            else if (ratio > 0.125)
                lifeRect.setFillColor({ 255, 165, 0 });
            else
                lifeRect.setFillColor(sf::Color::Red);

            auto borderSize = _sprite.getLocalSize();
            _sprite.setScale(life.relative.sx / borderSize.x, life.relative.sy / borderSize.y);
            _sprite.setPosition((int)transform.pos.x + life.relative.x, (int)transform.pos.y + life.relative.y);

            window->draw(backRect);
            window->draw(lifeRect);
            window->draw(_sprite.sprite);
        }
    }

    static std::shared_ptr<LifeSystem> create(Coordinator &ecs, const Sprite &sprite) {
        ecs.registerComponentIfNotExist<Life>();

        auto renderSystem = ecs.registerSystem<LifeSystem>();
        renderSystem->_sprite = sprite;
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Life>());
            signature.set(ecs.getComponentType<Transform>());
            ecs.setSystemSignature<LifeSystem>(signature);
        }
        return renderSystem;
    }

private:
    Sprite _sprite;
};

} // namespace ve

#endif /* !LIFESYSTEM_HPP_ */
