/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Shader
*/

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <SFML/Graphics/Shader.hpp>

namespace ve {

class Shader {
public:
    Shader(){};

    enum Type {
        Vertex = sf::Shader::Type::Vertex,
        Geometry = sf::Shader::Type::Geometry,
        Fragment = sf::Shader::Type::Fragment
    };

    bool loadFromFile(const std::string &filename, Type type) {
        return _shader.loadFromFile(filename, (sf::Shader::Type)type);
    }

    bool loadFromMemory(const std::string &shader, Type type) {
        return _shader.loadFromMemory(shader, (sf::Shader::Type)type);
    }

    void setUniform(const std::string &name) {
        _shader.setUniform(name, sf::Shader::CurrentTexture);
    }

    void setUniform(const std::string &name, float x) {
        _shader.setUniform(name, x);
    }

    sf::Shader &getShader() {
        return _shader;
    }

    sf::Shader _shader;
};

} // namespace ve

#endif /* !SHADER_HPP_ */
