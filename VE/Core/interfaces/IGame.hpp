/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "VE/Core/classes/Clock.hpp"
#include "VE/Core/managers/AssetsManager.hpp"
#include "VE/Core/managers/NetworkManager.hpp"
#include "VE/Core/managers/SceneManager.hpp"
#include "VE/Core/managers/WindowManager.hpp"
#include <list>
#include <memory>

namespace ve {

class IGame {
public:
    IGame(int &argc, char **argv) : argc(argc), argv(argv) {
        static const char *const empty = "";
        if (argc == 0 || argv == nullptr) {
            argc = 0;
            argv = const_cast<char **>(&empty);
        }
    }

    virtual ~IGame(){};

    int run() {
        _running = true;

        // Load assets
        initAssetHandlers();

        _assetsM.loadAll();

        // Load settings
        initSettingsConfig();

        // Try to open the Renderer window to display graphics
        initRender();

        initFactoryScreen();

        gameLoop();

        // Cleanup our application
        handleCleanup();

        // internal cleanup
        cleanup();
        return _exitCode;
    }

    // [Required]
    virtual void initRender() = 0;
    virtual void gameLoop() = 0;

    // [Optional]
    virtual void initAssetHandlers() {}
    virtual void initSettingsConfig() {}
    virtual void initFactoryScreen() {}
    virtual void handleCleanup() {}
    virtual void cleanup() {}

private:
    int _exitCode = 0;
    bool _running = false;

protected:
    std::unique_ptr<WindowManager> _windowM;
    AssetsManagers _assetsM;
    //NetworkManager _networkM;
    SceneManager _sceneM;
    Clock _clock;
    int argc;
    char **argv;
};

} // namespace ve

#endif /* !IGAME_HPP_ */