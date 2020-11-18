/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
#define IEVENT_HPP_

#include <SFML/Graphics.hpp>

namespace ve {

class IEvent {
public:
    enum class Type {
        Closed
    };

    virtual void action(Type) = 0;
    virtual void keyboard(sf::Keyboard::Key, sf::Event::EventType) = 0;
    virtual void mouse(sf::Mouse::Button, sf::Event::EventType) {}
};

} // namespace ve

#endif /* !IEVENT_HPP_ */
