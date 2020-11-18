/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <chrono>
#include <random>

namespace ve {

int randInt(int min, int max) {
    static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

} // namespace ve

#endif /* !RANDOM_HPP_ */