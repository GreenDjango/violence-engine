/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/systems/CollisionSystem/Arbiter.hpp"

#include <iostream>
#include <set>

namespace ve {

class CollisionSystem : public ecs::System {
public:
    static std::shared_ptr<CollisionSystem> create(Coordinator &ecs,
                                                   Vec2d gravity = { 0.0f, -10.0f },
                                                   int iterations = 10) {
        ecs.registerComponentIfNotExist<RigidBody>();
        ecs.registerComponentIfNotExist<Transform>();

        auto collisionSystem = ecs.registerSystem<CollisionSystem>();
        collisionSystem->gravity = gravity;
        collisionSystem->iterations = iterations;
        collisionSystem->accumulateImpulses = true;
        collisionSystem->warmStarting = true;
        collisionSystem->positionCorrection = true;
        collisionSystem->applyForces = false;
        {
            ecs::Signature signature;
            signature.set(ecs.getComponentType<RigidBody>());
            signature.set(ecs.getComponentType<Transform>());
            ecs.setSystemSignature<CollisionSystem>(signature);
        }
        return collisionSystem;
    }

    void Update(Coordinator &ecs, float deltaTime) {

        float inv_dt = deltaTime > 0.0f ? 1.0f / deltaTime : 0.0f;

        // Determine overlapping bodies and update contact points.
        BroadPhase(ecs);

        if (!applyForces)
            return;

        // Integrate forces.
        for (auto entity : ecs::System::entites) {
            RigidBody &b = ecs.getComponent<RigidBody>(entity);

            if (b.invMass == 0.0f)
                continue;

            b.velocity += (b.force * b.invMass + gravity) * deltaTime;
            b.angularVelocity += deltaTime * b.invI * b.torque;
        }

        // Perform pre-steps.
        for (auto arb = arbiters.begin(); arb != arbiters.end(); ++arb) {
            arb->second.PreStep(ecs, inv_dt, positionCorrection, accumulateImpulses);
        }

        //for (int i = 0; i < (int)joints.size(); ++i) {
        //    joints[i]->PreStep(inv_dt);
        //}

        // Perform iterations
        for (int i = 0; i < iterations; ++i) {
            for (auto arb = arbiters.begin(); arb != arbiters.end(); ++arb) {
                arb->second.ApplyImpulse(ecs, accumulateImpulses);
            }

            //for (int j = 0; j < (int)joints.size(); ++j) {
            //    joints[j]->ApplyImpulse();
            //}
        }

        // Integrate Velocities
        for (auto entity : ecs::System::entites) {
            RigidBody &b = ecs.getComponent<RigidBody>(entity);
            Transform &t = ecs.getComponent<Transform>(entity);

            if (b.invMass == 0.0f)
                continue;
            auto pos = b.velocity * deltaTime;
            t.pos.x += pos.x;
            t.pos.y += pos.y;
            //t.rot += b.angularVelocity * deltaTime;

            b.force = { 0.0f };
            b.torque = 0.0f;
            b.velocity = 0.0f;
        }
    }

    //void Add(Joint *joint) {
    //    joints.push_back(joint);
    //}

    void Clear() {
        //joints.clear();
        arbiters.clear();
    }

private:
    void BroadPhase(Coordinator &ecs) {
        std::set<ecs::Entity> destroyed;
        // TODO O(n^2) broad-phase, need to use AABB tree or grid for more speed
        for (auto it1 = ecs::System::entites.begin(); it1 != ecs::System::entites.end(); it1++) {
            for (auto it2 = it1; ++it2 != ecs::System::entites.end();) {
                RigidBody &b1 = ecs.getComponent<RigidBody>(*it1);
                RigidBody &b2 = ecs.getComponent<RigidBody>(*it2);

                if (b1.invMass == 0.0f && b2.invMass == 0.0f)
                    continue;

                Arbiter newArb(ecs, *it1, *it2);
                ArbiterKey key(*it1, *it2);

                if (newArb.numContacts > 0 && b1.mass >= 0 && b2.mass >= 0) {
                    if (b1.invMass > 0.0f) {
                        // auto &tr1 = ecs.getComponent<Transform>(*it1);
                        // auto &tr2 = ecs.getComponent<Transform>(*it2);
                        // auto nor = newArb.contacts->normal;

                        // if (nor.x == -1 && nor.y == 0)
                        //     tr1.pos.x = tr2.pos.x + b2.pos.x + b2.width.x - b1.pos.x + 1;
                        // else if (nor.x == 1 && nor.y == 0)
                        //     tr1.pos.x = tr2.pos.x + b2.pos.x - b1.width.x - b1.pos.x - 1;
                        // else if (nor.x == 0 && nor.y == -1)
                        //     tr1.pos.y = tr2.pos.y + b2.pos.y + b2.width.y - b1.pos.y;
                        // else if (nor.x == 0 && nor.y == 1)
                        //     tr1.pos.y = tr2.pos.y + b2.pos.y - b1.width.y - b1.pos.y;
                    }

                    auto iter = arbiters.find(key);
                    if (iter == arbiters.end()) {
                        arbiters.insert(std::pair<ArbiterKey, Arbiter>(key, newArb));
                    } else {
                        iter->second.Update(newArb.contacts, newArb.numContacts, warmStarting);
                    }
                } else if (newArb.numContacts > 0) {
                    if (b1.onCollision)
                        b1.onCollision(ecs, *it1, *it2, destroyed);
                    if (b2.onCollision)
                        b2.onCollision(ecs, *it2, *it1, destroyed);
                } else {
                    arbiters.erase(key);
                }
            }
        }
        for (auto e : destroyed)
            ecs.destroyEntity(e);
    }

    //std::vector<Joint *> joints;
    std::map<ArbiterKey, Arbiter> arbiters;
    Vec2d gravity;
    int iterations;
    bool accumulateImpulses;
    bool warmStarting;
    bool positionCorrection;
    bool applyForces;
};

} // namespace ve

#endif /* !COLLISIONSYSTEM_HPP_ */
