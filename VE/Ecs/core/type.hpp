/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** type
*/

#ifndef TYPE_ECS_HPP_
#define TYPE_ECS_HPP_

#include <bitset>

namespace ve::ecs {

using Entity = std::size_t;
constexpr Entity MAX_ENTITIES = 5000;
constexpr Entity MAX_COMPONENTS = 25;
using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentType = std::uint8_t;
using TypeName = const char *;

} // namespace ve::ecs

#endif /* !TYPE_ECS_HPP_ */
