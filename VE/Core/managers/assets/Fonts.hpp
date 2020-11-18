/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Fonts
*/

#ifndef FONTS_HPP_
#define FONTS_HPP_

#include "VE/Core/interfaces/IAssetManager.hpp"
#include "VE/Core/managers/PathManager.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>
#include <map>

namespace ve {

class Fonts : public IAssetManager {
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

    sf::Font &getRessource(const char *name) {
        return _fonts[name];
    }

private:
    std::map<std::string const, std::string const> _entries;
    std::map<std::string const, sf::Font> _fonts;

    void load() {
        for (auto &entry : _entries) {
            sf::Font font;
            if (!font.loadFromFile(entry.second))
                throw std::runtime_error("Can't load assets \'" + entry.first + "\' from \'" + entry.second + "\'");
            _fonts[entry.first] = font;
        }
    }
};

} // namespace ve

#endif /* !FONTS_HPP_ */
