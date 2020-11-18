/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Keyboard
*/

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "VE/Ecs.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

namespace ve {

using keyCallBack = std::function<void(Coordinator &, ecs::Entity, int, bool)>;

struct Keyboard {
    std::map<int, std::pair<sf::Keyboard::Key, keyCallBack>> keys;
    bool block;
};

} // namespace ve

#endif /* !KEYBOARD_HPP_ */
