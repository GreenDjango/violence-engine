/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Size
*/

#ifndef SIZE_HPP_
#define SIZE_HPP_

struct Size {
    unsigned int sx;
    unsigned int sy;

    Size()
        : sx{ 0 }, sy{ 0 } {
    }

    Size(unsigned int n)
        : sx{ n }, sy{ n } {
    }

    Size(unsigned int nx, unsigned int ny)
        : sx{ nx }, sy{ ny } {
    }
};

#endif /* !SIZE2D_HPP_ */
