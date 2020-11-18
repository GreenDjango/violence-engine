/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <SFML/System/Clock.hpp>

namespace ve {

class Clock {

public:
    float getElapsedSec() const {
        return _clock.getElapsedTime().asSeconds();
    }

    unsigned int getElapsedMs() const {
        return _clock.getElapsedTime().asMilliseconds();
    }

    void restart() {
        _clock.restart();
    }

    bool operator==(const Clock right) const {
        return this->_clock.getElapsedTime() == right._clock.getElapsedTime();
    }

    unsigned int operator-(const Clock right) const {
        return this->getElapsedMs() - right.getElapsedMs();
    }

private:
    sf::Clock _clock;
};

} // namespace ve

#endif /* !CLOCK_HPP_ */
