/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** SystemFactory
*/

#ifndef SYSTEMFACTORY_HPP_
#define SYSTEMFACTORY_HPP_

#include "VE/Ecs/core/type.hpp"
#include <list>
#include <memory>
#include <unordered_map>

namespace ve::ecs {

class System {
public:
    std::list<Entity> entites;
};

class SystemFactory {
public:
    template <typename T>
    std::shared_ptr<T> create() {
        const char *typeName = typeid(T).name();
        assert(_systems.find(typeName) == _systems.end() && "System already registred.");
        std::shared_ptr<T> system = std::shared_ptr<T>(new T());
        _systems.insert({ typeName, system });
        return system;
    }

    template <typename T>
    void assign(Signature signature) {
        const char *typeName = typeid(T).name();
        assert(_systems.find(typeName) != _systems.end() && "System used before registered.");
        _signatures.insert({ typeName, signature });
    }

    void onEntityDestroy(Entity entity) {
        for (auto const &pair : _systems) {
            auto const &system = pair.second;
            system->entites.remove(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature) {
        for (auto const &pair : _systems) {
            auto const &type = pair.first;
            auto const &system = pair.second;
            auto const &systemSignature = _signatures[type];

            if ((entitySignature & systemSignature) == systemSignature) {
                if (std::find(system->entites.begin(), system->entites.end(), entity) == system->entites.end())
                    system->entites.push_back(entity);
            } else
                system->entites.remove(entity);
        }
    }

private:
    std::unordered_map<const char *, Signature> _signatures{};
    std::unordered_map<const char *, std::shared_ptr<System>> _systems{};
};

} // namespace ve::ecs

#endif /* !SYSTEMFACTORY_HPP_ */
