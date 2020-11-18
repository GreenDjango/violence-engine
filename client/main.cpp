/*
** VE PROJECT, 2020
** VIOLENCE Engine
** File description:
** main test
*/

#include "VE/Core.hpp"
#include "VE/Ecs.hpp"
#include "VE/Ecs/basic.hpp"

#include <iostream>
#include <string.h>

class SplashScreenScene : public ve::IScene {
public:
    SplashScreenScene(ve::AssetsManagers &assets, ve::SceneManager &sceneManager)
        : IScene{ assets }, _sceneManager{ sceneManager }, logoFade{ false }, logoIntens{ 1 } {
        _renderSystem = ve::RenderSystem::create(_ecs);
        _transiSystem = ve::TransitionSystem::create(_ecs);
        _animatorSystem = ve::AnimatorSystem::create(_ecs);
        _uiSystem = ve::UiSystem::create(_ecs);
        setup();
    }

    void setup() {
        // Logo
        _logo = _ecs.createEntity();
        auto &fx = _ecs.assignComponent<ve::FxShader>(_logo, ve::FxShader::create(true, true, true));
        fx.shader.loadFromFile(ve::PathManager::getAbs("assets/vortex.frag"), ve::Shader::Fragment);
        fx.shader.setUniform("texture");
        auto &sprite = _ecs.assignComponent<ve::Sprite>(_logo, ve::Sprite{ __asset.get<ve::Textures>()->getRessource("violenceLogo") });
        sprite.setColor({ 255, 0 });
        _ecs.assignComponent<ve::UiTrigger>(_logo, ve::UiTrigger::create(ve::Align::CenterTop, { 1, 10 }, { 0, 1 }));
        _ecs.assignComponent<ve::Transform>(_logo, ve::Transform{ { 0 }, 0, { 0.7f }, { 0 } });
        // Text
        auto name = _ecs.createEntity();
        _ecs.assignComponent<ve::UiTrigger>(name, ve::UiTrigger::create(ve::Align::CenterTop, { 1, 10 }, { 0, 6 }));
        _ecs.assignComponent<ve::Text>(name, ve::Text{ L"made with VIOLENCE Engine™", __asset.get<ve::Fonts>()->getRessource("FiraSans-Reg") });
        _ecs.assignComponent<ve::Transform>(name, ve::Transform{ { 0 }, 0, { 1 }, { 0 } });
        _ecs.assignComponent<ve::Sprite>(name, ve::Sprite{});
    }

    virtual void update(float deltaTime) {
        _transiSystem->Update(_ecs, deltaTime);
        _animatorSystem->Update(_ecs, deltaTime);
        _uiSystem->Update(_ecs, deltaTime);
        if (logoIntens > 0.02f) {
            logoIntens -= 0.005f;
            auto &fx = _ecs.getComponent<ve::FxShader>(_logo);
            fx.intensityVal = logoIntens;
        }
        if (!logoFade) {
            logoFade = true;
            _ecs.assignComponent<ve::Transition>(_logo, ve::Transition::create(ve::Color{ 255, 0 }, ve::Color{ 255, 255 }, 1500));
        }
    }

    virtual void keyboard(sf::Keyboard::Key key, sf::Event::EventType type) {
        if (key == sf::Keyboard::Space && type == sf::Event::KeyPressed) {
            // Next...
        }
    }

    virtual void draw(ve::WindowManager *window) {
        _renderSystem->Update(_ecs, window);
    }

    ~SplashScreenScene(){};

private:
    ve::Coordinator _ecs;
    ve::SceneManager &_sceneManager;
    std::shared_ptr<ve::RenderSystem> _renderSystem;
    std::shared_ptr<ve::TransitionSystem> _transiSystem;
    std::shared_ptr<ve::AnimatorSystem> _animatorSystem;
    std::shared_ptr<ve::UiSystem> _uiSystem;
    ve::ecs::Entity _logo;
    bool logoFade;
    float logoIntens;
};

class RType : public ve::IGame, ve::IEvent {
public:
    RType(int &argc, char **argv) : IGame(argc, argv) {}

private:
    void initAssetHandlers() {
        auto textureManager = _assetsM.create<ve::Textures>();
        textureManager->addEntryFromFile({ { "violenceLogo", "assets/violence_logo.png" } });
        auto fontManager = _assetsM.create<ve::Fonts>();
        fontManager->addEntryFromFile({ {"FiraSans-Reg", "assets/FiraSans-Regular.ttf"}});
        auto musicManager = _assetsM.create<ve::Musics>();
        // musicManager->addEntryFromFile({ });
    }

    void initRender() {
        _windowM.reset(new ve::WindowManager{ "Test", 1920, 1080 });
        _windowM->setOption(ve::WindowManager::Option::vertical_sync, true);
        auto &logo = _assetsM.get<ve::Textures>()->getRessource("violenceLogo");
        _windowM->setIcon(logo.getSize().x, logo.getSize().y, logo);
        // auto &cursor = _assetsM.get<ve::Textures>()->getRessource("cursor");
        // _windowM->setMouseCursor({ 32, 32 }, cursor, { 16, 16 });
    }

    void action(ve::IEvent::Type action) {
        if (action == ve::IEvent::Type::Closed)
            _windowM->close();
    }

    void keyboard(sf::Keyboard::Key key, sf::Event::EventType event) {
        if (key == sf::Keyboard::Escape)
            _windowM->close();
        _sceneM.getActual()->keyboard(key, event);
    }

    void gameLoop() {
        _sceneM.add(std::shared_ptr<ve::IScene>(new SplashScreenScene(_assetsM, _sceneM)), "splash");
        _sceneM.switchTo("splash");
        while (_windowM->isOpen()) {
            _windowM->event(*this);
            float deltaTime = _clock.getElapsedSec();
            _clock.restart();
            _sceneM.update(deltaTime);
            _windowM->beginDraw();
            _sceneM.draw(_windowM.get());
            _windowM->endDraw();
            _sceneM.getActual()->lateUpdate(deltaTime);
        }
    }
};

int main(int argc, char *argv[]) {

    int exitCode = ve::StatusNoError;

    ve::IGame *rtype = new (std::nothrow) RType(argc, argv);
    assert(rtype != nullptr && "Can't create Game");

    exitCode = rtype->run();

    delete rtype;
    rtype = nullptr;

    return exitCode;
}
