/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Pos
*/

#ifndef POS_HPP_
#define POS_HPP_

struct Pos {
    int x;
    int y;

    Pos()
        : x{ 0 }, y{ 0 } {
    }

    Pos(int n)
        : x{ n }, y{ n } {
    }

    Pos(int nx, int ny)
        : x{ nx }, y{ ny } {
    }
};

#endif /* !POS_HPP_ */
