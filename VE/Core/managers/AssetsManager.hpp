/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** AssetsManagers
*/

#ifndef ASSETSMANAGERS_HPP_
#define ASSETSMANAGERS_HPP_

#include "VE/Core/interfaces/IAssetManager.hpp"
#include <cassert>
#include <map>
#include <memory>

namespace ve {

class AssetsManagers {
public:
    template <typename T>
    std::shared_ptr<T> create() {
        const char *typeName = typeid(T).name();
        assert(_assetsManagers.find(typeName) == _assetsManagers.end() && "AssetManager already registred.");
        std::shared_ptr<T> manager = std::shared_ptr<T>(new T());
        _assetsManagers.insert({ typeName, manager });
        return manager;
    }

    template <typename T>
    std::shared_ptr<T> get() {
        const char *typeName = typeid(T).name();
        auto it = _assetsManagers.find(typeName);
        assert(it != _assetsManagers.end() && "AssetManager not registred.");
        return std::static_pointer_cast<T>(it->second);
    }

    void loadAll() {
        for (auto &manager : _assetsManagers)
            manager.second->load();
    }

private:
    std::map<const char *, std::shared_ptr<IAssetManager>> _assetsManagers;
};

} // namespace ve

#endif /* !ASSETSMANAGERS_HPP_ */
