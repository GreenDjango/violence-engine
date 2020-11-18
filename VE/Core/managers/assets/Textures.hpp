/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Textures
*/

#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include "VE/Core/interfaces/IAssetManager.hpp"
#include "VE/Core/managers/PathManager.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>
#include <map>

namespace ve {

class Textures : public IAssetManager {
public:
    void addEntryFromFile(std::map<std::string const, std::string const> entries) {
        for (auto &entry : entries) {
            assert(_entries.find(entry.first) == _entries.end() && "Texture already loaded");
            if (entry.second[0] == '/')
                _entries.insert(entry);
            else
                _entries.insert({ entry.first, PathManager::getAbs(entry.second) });
        }
    }

    void addEntryFromFile(std::string const name, std::string const path) {
        assert(_entries.find(name) == _entries.end() && "Texture already loaded");
        _entries.insert({ name, (path[0] == '/') ? path : PathManager::getAbs(path) });
    }

    sf::Texture &getRessource(const char *name) {
        return _textures[name];
    }

private:
    std::map<std::string const, std::string const> _entries;
    std::map<std::string const, sf::Texture> _textures;

    void load() {
        for (auto &entry : _entries) {
            sf::Texture texture;
            if (!texture.loadFromFile(entry.second))
                throw std::runtime_error("Can't load assets \'" + entry.first + "\' from \'" + entry.second + "\'");
            _textures[entry.first] = texture;
        }
    }
};

} // namespace ve

#endif /* !TEXTURES_HPP_ */
