/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** TimeEvent
*/

#ifndef TIMEEVENT_HPP_
#define TIMEEVENT_HPP_

#include "VE/Ecs.hpp"
#include <functional>

namespace ve {

using timeCallBack = std::function<void(Coordinator &, ecs::Entity)>;

struct EventCall {
    unsigned int delay;
    unsigned int elapsed;
    timeCallBack func;
    bool enable;
};

struct TimeEvent {
    std::map<const char *, EventCall> events;
};

} // namespace ve

#endif /* !TIMEEVENT_HPP_ */
