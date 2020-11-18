/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "VE/Core/managers/WindowManager.hpp"

namespace ve {

class IScene {
public:
    virtual void onActivate(){};
    virtual void onDesactivate(){};
    virtual void keyboard(sf::Keyboard::Key, sf::Event::EventType){};
    virtual void mousse(){};
    virtual void action(){};
    virtual void update(float) = 0;
    virtual void lateUpdate(float){};
    virtual void draw(WindowManager *) = 0;

    IScene(ve::AssetsManagers &asset)
        : __asset{ asset } {}
    virtual ~IScene(){};

protected:
    ve::AssetsManagers &__asset;
};

} // namespace ve

#endif /* !ISCENE_HPP_ */
