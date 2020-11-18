/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "VE/Core/classes/Color.hpp"
#include <SFML/Graphics.hpp>

namespace ve {

class Sprite {
public:
    Sprite() {}

    Sprite(sf::Texture const &texture)
        : sprite{ texture } {}

    void setColor(Color const &col) {
        sprite.setColor(col._color);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    };

    void setScale(float factorX, float factorY) {
        sprite.setScale(factorX, factorY);
    };

    Vec2d getLocalSize() const {
        return { sprite.getLocalBounds().width, sprite.getLocalBounds().height };
    };

    Vec2d getGlobalSize() const {
        return { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height };
    };

    sf::Sprite sprite;
};

} // namespace ve

#endif /* !SPRITE_HPP_ */
