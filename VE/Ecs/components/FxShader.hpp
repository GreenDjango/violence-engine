/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** FxShader
*/

#ifndef FXSHADER_HPP_
#define FXSHADER_HPP_

#include "VE/Core/classes/Shader.hpp"

namespace ve {

struct FxShader {
    Shader shader;
    bool enable;
    bool timer;
    bool intensity;
    bool rand;
    float intensityVal;

    FxShader()
        : enable(false), timer(false), intensity(false), rand(false), intensityVal(0) {}

    FxShader(const FxShader &fx)
        : enable(fx.enable), timer(fx.timer), intensity(fx.intensity), rand(fx.rand), intensityVal(fx.intensityVal) {}

    FxShader(bool enable, bool timer, bool intensity = false, bool rand = false)
        : enable(enable), timer(timer), intensity(intensity), rand(rand), intensityVal(0) {}

    static FxShader create(bool enable, bool timer = false, bool intensity = false, bool rand = false) {
        return { enable, timer, intensity, rand };
    }

    FxShader &operator=(const FxShader &fx) {
        enable = fx.enable;
        timer = fx.timer;
        intensity = fx.intensity;
        rand = fx.rand;
        intensityVal = fx.intensityVal;
        return *this;
    }
};

} // namespace ve

#endif /* !FXSHADER_HPP_ */