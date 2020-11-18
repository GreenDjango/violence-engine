/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "VE/Maths/Vec2d.hpp"
#include <SFML/Graphics.hpp>

namespace ve {

class Text {
public:
    enum Style {
        Regular = sf::Text::Style::Regular,
        Bold = sf::Text::Style::Bold,
        Italic = sf::Text::Style::Italic,
        Underlined = sf::Text::Style::Underlined,
        StrikeThrough = sf::Text::Style::StrikeThrough
    };

    Text() {}

    Text(const std::string &string, const sf::Font &font, unsigned int characterSize = 30)
        : _text{ string, font, characterSize } {}

    Text(const wchar_t *string, const sf::Font &font, unsigned int characterSize = 30)
        : _text{ string, font, characterSize } {}

    void set(const std::string &string) {
        _text.setString(string);
    }

    // void setFont(const Font &font);
    // void setCharacterSize(unsigned int size);
    // void setLineSpacing(float spacingFactor);
    // void setLetterSpacing(float spacingFactor);
    void setStyle(unsigned int style) {
        _text.setStyle(style);
    }
    // void setFillColor(const Color &color);
    // void setOutlineColor(const Color &color);
    // void setOutlineThickness(float thickness);
    void setPosition(const Vec2d &pos) {
        _text.setPosition(pos.x, pos.y);
    }
    // const String &getString() const;
    // const Font *getFont() const;
    // unsigned int getCharacterSize() const;
    // float getLetterSpacing() const;
    // float getLineSpacing() const;
    // Uint32 getStyle() const;
    // const Color &getFillColor() const;
    // const Color &getOutlineColor() const;
    // float getOutlineThickness() const;
    // Vector2f findCharacterPos(std::size_t index) const;
    // FloatRect getLocalBounds() const;
    Vec2d getGlobalSize() const {
        return { _text.getGlobalBounds().width, _text.getGlobalBounds().height };
    };

    sf::Text _text;
};

} // namespace ve

#endif /* !TEXT_HPP_ */
