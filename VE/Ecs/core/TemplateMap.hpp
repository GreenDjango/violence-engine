/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** TemplateMap
*/

#ifndef TEMPLATEMAP_HPP_
#define TEMPLATEMAP_HPP_

#include "VE/Ecs/core/type.hpp"
#include <unordered_map>

namespace ve::ecs {

class ITemplateMap {
public:
    virtual ~ITemplateMap() = default;
    virtual void onEntityDestroy(Entity entity) = 0;
};

template <typename T>
class TemplateMap : public ITemplateMap {
public:
    void insert(Entity entity, T component) {
        _components[entity] = component;
    }

    void remove(Entity entity) {
        auto it = _components.find(entity);
        if (it != _components.end())
            _components.erase(it);
    }

    T &get(Entity entity) {
        return _components[entity];
    }

    bool exist(Entity entity) {
        return (_components.find(entity) != _components.end());
    }

    void onEntityDestroy(Entity entity) override {
        remove(entity);
    }

private:
    std::unordered_map<Entity, T> _components;
};

} // namespace ve::ecs

#endif /* !TEMPLATEMAP_HPP_ */
