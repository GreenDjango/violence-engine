/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** _KeyboardSystem
*/

#ifndef _KEYBOARDSYSTEM_HPP_
#define _KEYBOARDSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/Keyboard.hpp"

namespace ve {

class KeyboardSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, sf::Keyboard::Key key, sf::Event::EventType type) {
        for (auto entity : ecs::System::entites) {
            auto &keyboard = ecs.getComponent<Keyboard>(entity);

            if (keyboard.block)
                continue;
            for (auto &_key : keyboard.keys)
                if (_key.second.first == key)
                    _key.second.second(ecs, entity, _key.first, (type == sf::Event::KeyPressed));
        }
    }

    static std::shared_ptr<KeyboardSystem> create(Coordinator &ecs) {
        ecs.registerComponentIfNotExist<Keyboard>();

        auto keyboardSystem = ecs.registerSystem<KeyboardSystem>();
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<Keyboard>());
            ecs.setSystemSignature<KeyboardSystem>(signature);
        }
        return keyboardSystem;
    }
};

} // namespace ve

#endif /* !_KEYBOARDSYSTEM_HPP_ */
