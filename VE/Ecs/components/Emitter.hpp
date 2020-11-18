/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Emitter
*/

#ifndef EMITTER_HPP_
#define EMITTER_HPP_

#include "VE/Core/classes/Color.hpp"
#include "VE/Maths/Vec2d.hpp"
#include "VE/Maths/Vec3d.hpp"
#include <cmath>
#include <memory>
#include <vector>

namespace ve {

class Shape {
public:
    virtual void setTexture(const sf::Texture *texture, bool resetRect = false) = 0;
    // void setTextureRect(const IntRect &rect);
    virtual void setFillColor(const Color &color) = 0;
    virtual void setOutlineColor(const Color &color) = 0;
    virtual void setOutlineThickness(float thickness) = 0;
    //const Texture *getTexture() const;
    //const IntRect &getTextureRect() const;
    virtual Color getFillColor() const = 0;
    virtual Color getOutlineColor() const = 0;
    //float getOutlineThickness() const;
    //virtual std::size_t getPointCount() const = 0;
    //virtual Vector2f getPoint(std::size_t index) const = 0;
    //FloatRect getLocalBounds() const;
    //FloatRect getGlobalBounds() const;
    virtual void setPosition(const Vec2d &position) = 0;
    virtual void setScale(const Vec2d &factors) = 0;
    virtual sf::Drawable const &getShape() = 0;
};

class RectShape : public Shape {
public:
    RectShape(const Vec2d &size = { 0 }) : _shape({ size.x, size.y }){};
    RectShape(float x, float y) : _shape({ x, y }){};
    void setTexture(const sf::Texture *texture, bool resetRect = false) { _shape.setTexture(texture, resetRect); };
    void setFillColor(const Color &color) { _shape.setFillColor(color._color); };
    void setOutlineColor(const Color &color) { _shape.setOutlineColor(color._color); };
    void setOutlineThickness(float thickness) { _shape.setOutlineThickness(thickness); };
    Color getFillColor() const { return _shape.getFillColor().toInteger(); };
    Color getOutlineColor() const { return _shape.getOutlineColor().toInteger(); };
    void setPosition(const Vec2d &position) { _shape.setPosition(position.x, position.y); };
    void setScale(const Vec2d &factors) { _shape.setScale(factors.x, factors.y); };
    sf::Drawable const &getShape() { return _shape; };

private:
    sf::RectangleShape _shape;
};

class CircleShape : public Shape {
public:
    CircleShape(float radius = 0, std::size_t pointCount = 30) : _shape(radius, pointCount){};
    void setTexture(const sf::Texture *texture, bool resetRect = false) { _shape.setTexture(texture, resetRect); };
    void setFillColor(const Color &color) { _shape.setFillColor(color._color); };
    void setOutlineColor(const Color &color) { _shape.setOutlineColor(color._color); };
    void setOutlineThickness(float thickness) { _shape.setOutlineThickness(thickness); };
    Color getFillColor() const { return _shape.getFillColor().toInteger(); };
    Color getOutlineColor() const { return _shape.getOutlineColor().toInteger(); };
    void setPosition(const Vec2d &position) { _shape.setPosition(position.x, position.y); };
    void setScale(const Vec2d &factors) { _shape.setScale(factors.x, factors.y); };
    sf::Drawable const &getShape() { return _shape; };

private:
    sf::CircleShape _shape;
};

class IEmitterRegion {
public:
    IEmitterRegion() {}
    virtual ~IEmitterRegion() {}

    // Get a Spawn point from the spawn region
    virtual Vec2d getPoint(const Vec2d &transform) = 0;
    // Call this function to check if there is direction vector avaiable for the last spawnpoint
    virtual bool isForceField(void) const {
        return false;
    }
};

class PointRegion : public IEmitterRegion {
public:
    PointRegion() {}
    PointRegion(const Vec2d &offset) : offset(offset) {}
    ///Get a Spawn point from the spawn region
    virtual Vec2d getPoint(const Vec2d &transform) {
        return transform + offset;
    }
    Vec2d offset;
};

class LineRegion : public IEmitterRegion {
public:
    LineRegion(const Vec2d &s, const Vec2d &e) : start(s), end(e) {}
    LineRegion(float x, float y, float a, float b) {
        start = Vec2d(x, y);
        end = Vec2d(a, b);
    }
    virtual Vec2d getPoint(const Vec2d &transform) {
        float r0 = ((float)(rand() % 100)) / 100.f;
        Vec2d vec = end - start;
        Vec2d point = start + vec * 0.5f;
        point += vec * (r0 - 0.5f);
        // printf("add: %f - %f, %f\n", r0, point.x, point.y);
        return transform + point;
    }
    Vec2d start;
    Vec2d end;
};

class RectRegion : public IEmitterRegion {
public:
    RectRegion(const Vec2d &s, const Vec2d &e) : start(s), end(e) {}
    RectRegion(float x, float y, float a, float b) {
        start = Vec2d(x, y);
        end = Vec2d(a, b);
    }
    virtual Vec2d getPoint(const Vec2d &transform) {
        float r0 = ((float)(rand() % 100)) / 100.f;
        Vec2d vec = end - start;
        Vec2d point = start + vec * r0;
        return transform + point;
    }
    Vec2d start;
    Vec2d end;
};

class CircleRegion : public IEmitterRegion {
public:
    CircleRegion(const Vec2d &center, float radius) : center(center), radius(radius) {}
    CircleRegion(float centerX, float centerY, float radius) : radius(radius) {
        center = Vec2d(centerX, centerY);
    }
    virtual Vec2d getPoint(const Vec2d &transform) {
        float r0 = ((float)(std::rand() % 100)) / 100.f;
        float r1 = ((float)(std::rand() % 100)) / 100.f;
        float rad = radius * std::sqrt(r0);
        float theta = r1 * 2 * M_PI;
        Vec2d point{ center.x + rad * std::cos(theta),
                     center.y + rad * std::sin(theta) };
        return transform + point;
    }
    Vec2d center;
    float radius;
};

struct Particle {
    Vec2d pos;
    Vec2d velocity;

    Vec2d scale;
    Vec2d startScale;
    Vec2d scaleSpeed;

    float lifeTime;
    float timeLeft;

    float fadePercent;

    Particle() {}

    Particle(float lifeTime, Vec2d velo = { 0 }, float fadePercent = 100, Vec2d startScale = { 1 },
             Vec2d scaleSpeed = { 0 })
        : velocity(velo), scale(startScale), startScale(startScale),
          scaleSpeed(scaleSpeed), lifeTime(lifeTime), timeLeft(0), fadePercent(fadePercent) {}

    /*
    Vec3d Position;
    Vec3d Speed;
    Vec3d StartSpeed;

    irr::video::SColor Color;
    irr::video::SColor StartColor;
    */
};

struct Emitter {
    std::vector<Particle> particles;
    // unsigned int msElapsed;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<IEmitterRegion> region;

    Emitter() {}
    Emitter(Shape *shape, IEmitterRegion *region) : shape(shape), region(region) {}
};

} // namespace ve

#endif /* !EMITTER_HPP_ */