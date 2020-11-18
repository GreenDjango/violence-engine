/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SFML/Graphics/Color.hpp>

namespace ve {

class Color {
public:
    Color(){};
    Color(unsigned char color, unsigned char alpha) : _color(color, color, color, alpha){};
    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) : _color(red, green, blue, alpha){};
    Color(unsigned int color) : _color(color){};

    unsigned char a() const {
        return _color.a;
    }

    void setA(unsigned char alpha) {
        _color.a = alpha;
    }

    unsigned int toInteger() const {
        return _color.toInteger();
    }

    Color operator+(const Color &other) const {
        return ((*this)._color + other._color).toInteger();
    }
    Color operator-(const Color &other) const {
        return ((*this)._color - other._color).toInteger();
    }
    Color operator*(const Color &other) const {
        return ((*this)._color * other._color).toInteger();
    }
    Color operator*(float f) const {
        return { (unsigned char)(this->_color.r * f),
                 (unsigned char)(this->_color.g * f),
                 (unsigned char)(this->_color.b * f),
                 (unsigned char)(this->_color.a * f) };
    }
    Color &operator+=(const Color &other) {
        this->_color += other._color;
        return *this;
    }

    sf::Color _color;
};

} // namespace ve

#endif /* !COLOR_HPP_ */
