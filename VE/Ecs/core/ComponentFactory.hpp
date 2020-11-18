/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include "VE/Ecs/core/TemplateMap.hpp"
#include "VE/Ecs/core/type.hpp"
#include <memory>
#include <unordered_map>

namespace ve::ecs {

class ComponentFactory {
public:
    template <typename T>
    void create() {
        TypeName name = typeid(T).name();
        assert(_registredComponent.find(name) == _registredComponent.end() && "Component already registred.");
        _registredComponent.insert({ name, _nextId });
        _componentsMap.insert({ name, std::shared_ptr<ITemplateMap>(new TemplateMap<T>()) });
        _nextId++;
    }

    template <typename T>
    bool exist() {
        const char *typeName = typeid(T).name();
        return (_registredComponent.find(typeName) != _registredComponent.end());
    }

    template <typename T>
    ComponentType getType() {
        TypeName name = typeid(T).name();
        assert(_registredComponent.find(name) != _registredComponent.end() && "Component not registred.");
        return _registredComponent[name];
    }

    template <typename T>
    void assign(Entity entity, T component) {
        _getComponentMap<T>()->insert(entity, component);
    }

    template <typename T>
    void unassign(Entity entity) {
        _getComponentMap<T>()->remove(entity);
    }

    template <typename T>
    T &get(Entity entity) {
        return _getComponentMap<T>()->get(entity);
    }

    template <typename T>
    bool exist(Entity entity) {
        return _getComponentMap<T>()->exist(entity);
    }

    void onEntityDestroy(Entity entity) {
        for (auto &pair : _componentsMap)
            pair.second->onEntityDestroy(entity);
    }

private:
    std::unordered_map<TypeName, ComponentType> _registredComponent;
    std::unordered_map<TypeName, std::shared_ptr<ITemplateMap>> _componentsMap;
    std::size_t _nextId{ 0 };

    template <typename T>
    std::shared_ptr<TemplateMap<T>> _getComponentMap() {
        TypeName typeName = typeid(T).name();
        assert(_registredComponent.find(typeName) != _registredComponent.end() && "Component not registered.");
        return std::static_pointer_cast<TemplateMap<T>>(_componentsMap[typeName]);
    }
};

} // namespace ve::ecs

#endif /* !COMPONENTFACTORY_HPP_ */