/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** DebugSystem
*/

#ifndef DEBUGSYSTEM_HPP_
#define DEBUGSYSTEM_HPP_

#include "VE/Core/managers/WindowManager.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/components/DebugDraw.hpp"

namespace ve {

class DebugSystem : public ecs::System {
public:
    void Update(Coordinator &ecs, WindowManager *window) {
        Size win = window->getSize();
        for (auto entity : ecs::System::entites) {
            auto &debug = ecs.getComponent<DebugDraw>(entity);

            Text text{ "FPS: " + toString(debug.getFps()) +
                           "\nSleep: " + toString(debug.getSleepAverage() * 1000.f) +
                           "ms\nDraw: " + toString(debug.getDrawAverage() * 1000.f) +
                           "ms\nPhysics: " + toString(debug.getPhysicAverage() * 1000.f) + "ms",
                       _font, 20 };
            auto size = text.getGlobalSize();
            size.x += 10;
            Vec2d pos;

            if (debug.align & AlignFlag::FlagLeft) {
                // pos.x == 0 by default
            } else if (debug.align & AlignFlag::FlagHCenter) {
                pos.x = win.sx / 2 - size.x / 2;
            } else {
                pos.x = win.sx - size.x;
            }
            if (debug.align & AlignFlag::FlagBottom) {
                pos.y = win.sy - size.y;
            } else if (debug.align & AlignFlag::FlagVCenter) {
                pos.y = win.sy / 2 - size.y / 2;
            }
            text.setPosition(pos);
            window->draw(text._text);
            debug.updateFps();
        }
    }

    static std::shared_ptr<DebugSystem> create(Coordinator &ecs, sf::Font const &font) {
        ecs.registerComponentIfNotExist<DebugDraw>();

        auto debugSystem = ecs.registerSystem<DebugSystem>();
        debugSystem->_font = font;
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<DebugDraw>());
            ecs.setSystemSignature<DebugSystem>(signature);
        }
        return debugSystem;
    }

private:
    std::string toString(float f) {
        char str[11] = { 0 };
        std::snprintf(str, 10, "%.2f", f);
        return std::string{ str };
    }
    sf::Font _font;
};

} // namespace ve

#endif /* !DEBUGSYSTEM_HPP_ */
