/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** TypeEntity
*/

#ifndef TYPEENTITY_HPP_
#define TYPEENTITY_HPP_

namespace ve {

struct TypeEntity {
    enum target {
        Player = 0,
        Block,
        Mob
    };

    target type;
};

} // namespace ve

#endif /* !TYPEENTITY_HPP_ */
