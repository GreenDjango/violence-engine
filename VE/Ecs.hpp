/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Ecs
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include "VE/Ecs/core/ComponentFactory.hpp"
#include "VE/Ecs/core/EntityFactory.hpp"
#include "VE/Ecs/core/SystemFactory.hpp"
#include "VE/Ecs/core/type.hpp"
#include <memory>

namespace ve {

class Coordinator {
public:
    Coordinator()
        : _entityFactory{ new ecs::EntityFactory() }, _componentFactory{ new ecs::ComponentFactory() }, _systemFactory{ new ecs::SystemFactory() } {}

    ecs::Entity createEntity() {
        return _entityFactory->create();
    }

    void destroyEntity(ecs::Entity entity) {
        _entityFactory->destroy(entity);
        _componentFactory->onEntityDestroy(entity);
        _systemFactory->onEntityDestroy(entity);
    }

    // Component
    template <typename T>
    void registerComponent() {
        _componentFactory->create<T>();
    }

    template <typename T>
    void registerComponentIfNotExist() {
        if (!_componentFactory->exist<T>())
            registerComponent<T>();
    }

    // Variadic arg
    template <typename First, typename... Args>
    void assigns(ecs::Entity entity, First first, Args... args) {
        assigns(entity, first);
        assigns(entity, args...);
    }
    template <typename Args>
    void assigns(ecs::Entity entity, Args args) {
        assignComponent<Args>(entity, args);
    }
    // --

    template <typename T>
    T &assignComponent(ecs::Entity entity, T component) {
        _componentFactory->assign<T>(entity, component);
        ecs::Signature actual = _entityFactory->getSignature(entity);
        actual.set(_componentFactory->getType<T>());
        _entityFactory->setSignature(entity, actual);
        _systemFactory->entitySignatureChanged(entity, actual);
        return _componentFactory->get<T>(entity);
    }

    template <typename T>
    void unassignComponent(ecs::Entity entity) {
        _componentFactory->unassign<T>(entity);
        ecs::Signature actual = _entityFactory->getSignature(entity);
        actual.set(_componentFactory->getType<T>(), false);
        _entityFactory->setSignature(entity, actual);
        _systemFactory->entitySignatureChanged(entity, actual);
    }

    template <typename T>
    T &getComponent(ecs::Entity entity) {
        return _componentFactory->get<T>(entity);
    }

    template <typename T>
    bool hasComponent(ecs::Entity entity) {
        return _componentFactory->exist<T>(entity);
    }

    template <typename T>
    ecs::ComponentType getComponentType() {
        return _componentFactory->getType<T>();
    }

    template <typename T>
    std::shared_ptr<T> registerSystem() {
        return _systemFactory->create<T>();
    }

    template <typename T>
    void setSystemSignature(ecs::Signature signature) {
        _systemFactory->assign<T>(signature);
    }

private:
    std::unique_ptr<ecs::EntityFactory> _entityFactory;
    std::unique_ptr<ecs::ComponentFactory> _componentFactory;
    std::unique_ptr<ecs::SystemFactory> _systemFactory;
};

} // namespace ve

#endif /* !ECS_HPP_ */
