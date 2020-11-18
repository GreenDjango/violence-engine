/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Musics
*/

#ifndef MUSICS_HPP_
#define MUSICS_HPP_

#include "VE/Core/interfaces/IAssetManager.hpp"
#include "VE/Core/managers/PathManager.hpp"
#include <SFML/Audio.hpp>
#include <cassert>
#include <map>
#include <string>
#include <utility>

namespace ve {

class Musics : public IAssetManager {
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
        assert(_entries.find(name) == _entries.end() && "Font already loaded");
        _entries.insert({ name, (path[0] == '/') ? path : PathManager::getAbs(path) });
    }

    sf::Music &getRessource(const char *name) {
        return _musics[name];
    }

private:
    std::map<std::string const, std::string const> _entries;
    std::map<std::string const, sf::Music> _musics;

    void load() {
        for (auto &entry : _entries) {
            _musics.emplace(std::piecewise_construct, std::make_tuple(entry.first), std::make_tuple());
            if (!_musics[entry.first].openFromFile(entry.second))
                throw std::runtime_error("Can't load assets \'" + entry.first + "\' from \'" + entry.second + "\'");
        }
    }
};

} // namespace ve

#endif /* !MUSICS_HPP_ */
