/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include "VE/Core/interfaces/IScene.hpp"
#include "VE/Core/type.hpp"
#include "VE/Ecs/components/Emitter.hpp"
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>

namespace ve {

class SceneManager {
public:
    SceneManager() {
        _msRemaining = 0;
        _transitionDuration = 0;
    }

    std::shared_ptr<IScene> getActual() {
        if (!_current.second)
            throw std::runtime_error("Missing scene.");
        return _current.second;
    }

    void add(std::shared_ptr<IScene> scene, const std::string &name) {
        assert(_scenes.find(name) == _scenes.end() && "Scene already exist.");
        _scenes.insert({ name, scene });
    }

    void switchTo(const std::string &name) {
        if (_current.first == name)
            return;
        auto it = _scenes.find(name);
        if (it != _scenes.end()) {
            if (_current.second)
                _current.second->onDesactivate();
            _current = *it;
            _current.second->onActivate();
        } else
            assert(false && "Scene not found.");
    }

    void switchTo(const std::string &name, unsigned int fadeDuration) {
        if (_nextScene == name)
            return;
        if (fadeDuration <= 0)
            switchTo(name);
        else {
            _msRemaining = fadeDuration;
            _transitionDuration = fadeDuration;
            _nextScene = name;
        }
    }

    void remove(const std::string &name) {
        auto it = _scenes.find(name);
        if (it != _scenes.end()) {
            _current.second = nullptr;
            _scenes.erase(it);
        }
    }

    void update(float deltaTime) {
        getActual()->update(deltaTime);
        if (_msRemaining > 0) {
            _msRemaining -= deltaTime * 1000;
            float ratio = (float)_msRemaining / (float)_transitionDuration;
            if (!_nextScene.empty() && ratio <= 0.5f) {
                switchTo(_nextScene);
                _nextScene = "";
            }
        }
    }

    void draw(WindowManager *window) {
        getActual()->draw(window);
        if (_msRemaining > 0) {
            float ratio = (float)_msRemaining / (float)_transitionDuration;
            RectShape rect(window->getSize().sx, window->getSize().sy);
            rect.setFillColor({ 0, (unsigned char)(ratio >= 0.5f ? -(ratio - 1) * 510 : ratio * 510) });
            window->draw(rect.getShape());
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<IScene>> _scenes;
    std::pair<std::string, std::shared_ptr<IScene>> _current;
    std::size_t _length;
    int _msRemaining;
    int _transitionDuration;
    std::string _nextScene;
};

} // namespace ve

#endif /* !SCENEMANAGER_HPP_ */