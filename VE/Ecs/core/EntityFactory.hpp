/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include "VE/Ecs/core/type.hpp"
#include <array>
#include <cassert>
#include <queue>

namespace ve::ecs {

class EntityFactory {
public:
    // Genered all unused IDs
    EntityFactory() {
        for (Entity id = 0; id < MAX_ENTITIES; id++)
            _availableEntities.push(id);
    }

    // Take an unused ID
    Entity create() {
        assert(_aliveEntityCount < MAX_ENTITIES && "Entity limit reached.");
        Entity id = _availableEntities.front();
        _availableEntities.pop();
        _aliveEntityCount++;
        return id;
    }

    // Free ID and reset signature
    void destroy(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity is out of range.");
        _signatures[entity].reset();
        _availableEntities.push(entity);
        _aliveEntityCount--;
    }

    void setSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "Entity is out of range.");
        _signatures[entity] = signature;
    }

    Signature getSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity is out of range.");
        return _signatures[entity];
    }

private:
    // Unused entity IDs
    std::queue<Entity> _availableEntities{};
    // Array of signatures, index = entity ID
    std::array<Signature, MAX_ENTITIES> _signatures{};
    // Total alive entities - used to keep limits
    size_t _aliveEntityCount{};
};

} // namespace ve::ecs

#endif /* !ENTITYFACTORY_HPP_ */
