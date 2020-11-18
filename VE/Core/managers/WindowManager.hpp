/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** WindowManager
*/

#ifndef WINDOW_MANAGER_HPP_
#define WINDOW_MANAGER_HPP_

#include "VE/Core/interfaces/IEvent.hpp"
#include "VE/Maths/Size.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>

namespace ve {

class WindowManager {
public:
    enum class Option {
        vertical_sync,
        frame_limit,
    };

    enum WinStyle
    {
        None       = sf::Style::None,       ///< No border / title bar (this flag and all others are mutually exclusive)
        Titlebar   = sf::Style::Titlebar,   ///< Title bar + fixed border
        Resize     = sf::Style::Resize,     ///< Title bar + resizable border + maximize button
        Close      = sf::Style::Close,      ///< Title bar + close button
        Fullscreen = sf::Style::Fullscreen, ///< Fullscreen mode (this flag and all others are mutually exclusive)
        Default = sf::Style::Default        ///< Default window style
    };

    WindowManager(const std::string &name, std::size_t width, std::size_t height, WinStyle style = Default)
        : _window{ sf::VideoMode(width, height), name, style } {
        _window.setKeyRepeatEnabled(false);
    }

    void setOption(Option target, int value = 0) {
        switch (target) {
        case Option::vertical_sync:
            _window.setVerticalSyncEnabled(value);
            break;
        case Option::frame_limit:
            _window.setFramerateLimit(value);
            break;
        }
    }

    void setIcon(unsigned int width, unsigned int height, const sf::Texture &img) {
        _window.setIcon(width, height, img.copyToImage().getPixelsPtr());
    }

    void setMouseCursor(const Size &size, const sf::Texture &img, const Size &hotspot = { 0 }) {
        sf::Cursor cursor;
        cursor.loadFromPixels(img.copyToImage().getPixelsPtr(), { size.sx, size.sy }, { hotspot.sx, hotspot.sy });
        _window.setMouseCursor(cursor);
    }

    Size getSize() {
        return Size{ _window.getSize().x, _window.getSize().y };
    }

    void event(IEvent &manager) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                manager.action(IEvent::Type::Closed);
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                manager.keyboard(event.key.code, event.type);
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
                manager.mouse(event.mouseButton.button, event.type);
        }
    }

    void close() {
        assert(isOpen() == true && "window already closed");
        _window.close();
    }

    void beginDraw() {
        _window.clear(sf::Color::Black);
    }

    void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default) {
        _window.draw(drawable, states);
    }

    void endDraw() {
        _window.display();
    }

    bool isOpen() const {
        return _window.isOpen();
    }

private:
    sf::RenderWindow _window;
};

} // namespace ve

#endif /* !WINDOW_MANAGER_HPP_ */
