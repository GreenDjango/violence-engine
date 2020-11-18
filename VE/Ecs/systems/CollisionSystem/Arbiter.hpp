/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Arbiter
*/

#ifndef ARBITER_HPP_
#define ARBITER_HPP_

#include "VE/Ecs/systems/CollisionSystem/Collider.hpp"
#include "VE/Maths/Utils.hpp"

namespace ve {

struct ArbiterKey {
    ArbiterKey(ecs::Entity b1, ecs::Entity b2) {
        if (b1 < b2) {
            body1 = b1;
            body2 = b2;
        } else {
            body1 = b2;
            body2 = b1;
        }
    }

    bool operator<(const ArbiterKey &k) const {
        if (body1 < k.body1)
            return true;

        if (body1 == k.body1 && body2 < k.body2)
            return true;

        return false;
    }

    ecs::Entity body1;
    ecs::Entity body2;
};

struct Arbiter {
    enum { MAX_POINTS = 2 };

    Arbiter(Coordinator &ecs, ecs::Entity entityA, ecs::Entity entityB) {
        if (entityA < entityB) {
            entity1 = entityA;
            entity2 = entityB;
        } else {
            entity1 = entityB;
            entity2 = entityA;
        }

        numContacts = Collider::collide(contacts, ecs, entity1, entity2);

        friction = sqrtf(
            ecs.getComponent<RigidBody>(entity1).friction *
            ecs.getComponent<RigidBody>(entity2).friction);
    }

    void Update(Contact *newContacts, int numNewContacts, bool warmStarting = true) {
        Contact mergedContacts[2];

        for (int i = 0; i < numNewContacts; ++i) {
            Contact *cNew = newContacts + i;
            int k = -1;
            for (int j = 0; j < numContacts; ++j) {
                Contact *cOld = contacts + j;
                if (cNew->feature.value == cOld->feature.value) {
                    k = j;
                    break;
                }
            }

            if (k > -1) {
                Contact *c = mergedContacts + i;
                Contact *cOld = contacts + k;
                *c = *cNew;
                if (warmStarting) {
                    c->Pn = cOld->Pn;
                    c->Pt = cOld->Pt;
                    c->Pnb = cOld->Pnb;
                } else {
                    c->Pn = 0.0f;
                    c->Pt = 0.0f;
                    c->Pnb = 0.0f;
                }
            } else {
                mergedContacts[i] = newContacts[i];
            }
        }

        for (int i = 0; i < numNewContacts; ++i)
            contacts[i] = mergedContacts[i];

        numContacts = numNewContacts;
    }

    void PreStep(Coordinator &ecs, float inv_dt, bool positionCorrection = true, bool accumulateImpulses = true) {
        const float k_allowedPenetration = 0.01f;
        float k_biasFactor = positionCorrection ? 0.2f : 0.0f;

        auto &bodyTA = ecs.getComponent<Transform>(entity1);
        auto &bodyTB = ecs.getComponent<Transform>(entity2);
        auto &bodyRA = ecs.getComponent<RigidBody>(entity1);
        auto &bodyRB = ecs.getComponent<RigidBody>(entity2);

        for (int i = 0; i < numContacts; ++i) {
            Contact *c = contacts + i;

            Vec2d r1 = c->position - Vec2d{ bodyTA.pos.x + bodyRA.pos.x, bodyTA.pos.y + bodyRA.pos.y };
            Vec2d r2 = c->position - Vec2d{ bodyTB.pos.x + bodyRB.pos.x, bodyTB.pos.y + bodyRB.pos.y };

            // Precompute normal mass, tangent mass, and bias.
            float rn1 = r1.dot(c->normal);
            float rn2 = r2.dot(c->normal);
            float kNormal = bodyRA.invMass + bodyRB.invMass;
            kNormal += bodyRA.invI * (r1.dot(r1) - rn1 * rn1) + bodyRB.invI * (r2.dot(r2) - rn2 * rn2);
            c->massNormal = 1.0f / kNormal;

            Vec2d tangent = c->normal.cross(1.0f);
            float rt1 = r1.dot(tangent);
            float rt2 = r2.dot(tangent);
            float kTangent = bodyRA.invMass + bodyRB.invMass;
            kTangent += bodyRA.invI * (r1.dot(r1) - rt1 * rt1) + bodyRB.invI * (r2.dot(r2) - rt2 * rt2);
            c->massTangent = 1.0f / kTangent;

            c->bias = -k_biasFactor * inv_dt * std::min(0.0f, c->separation + k_allowedPenetration);

            if (accumulateImpulses) {
                // Apply normal + friction impulse
                Vec2d P = c->normal * c->Pn + tangent * c->Pt;

                bodyRA.velocity -= P * bodyRA.invMass;
                bodyRA.angularVelocity -= bodyRA.invI * r1.cross(P);

                bodyRB.velocity += P * bodyRB.invMass;
                bodyRB.angularVelocity += bodyRB.invI * r2.cross(P);
            }
        }
    }

    void ApplyImpulse(Coordinator &ecs, bool accumulateImpulses = true) {
        auto &bodyTA = ecs.getComponent<Transform>(entity1);
        auto &bodyTB = ecs.getComponent<Transform>(entity2);
        auto &bodyRA = ecs.getComponent<RigidBody>(entity1);
        auto &bodyRB = ecs.getComponent<RigidBody>(entity2);

        for (int i = 0; i < numContacts; ++i) {
            Contact *c = contacts + i;
            c->r1 = c->position - Vec2d{ bodyTA.pos.x + bodyRA.pos.x, bodyTA.pos.y + bodyRA.pos.y };
            c->r2 = c->position - Vec2d{ bodyTB.pos.x + bodyRB.pos.x, bodyTB.pos.y + bodyRB.pos.y };

            // Relative velocity at contact
            Vec2d dv = bodyRB.velocity + c->r2.cross(-bodyRB.angularVelocity) - bodyRA.velocity - c->r1.cross(-bodyRA.angularVelocity);

            // Compute normal impulse
            float vn = dv.dot(c->normal);

            float dPn = c->massNormal * (-vn + c->bias);

            if (accumulateImpulses) {
                // Clamp the accumulated impulse
                float Pn0 = c->Pn;
                c->Pn = std::max(Pn0 + dPn, 0.0f);
                dPn = c->Pn - Pn0;
            } else {
                dPn = std::max(dPn, 0.0f);
            }

            // Apply contact impulse
            Vec2d Pn = c->normal * dPn;

            bodyRA.velocity -= Pn * bodyRA.invMass;
            bodyRA.angularVelocity -= bodyRA.invI * c->r1.cross(Pn);

            bodyRB.velocity += Pn * bodyRB.invMass;
            bodyRB.angularVelocity += bodyRB.invI * c->r2.cross(Pn);

            // Relative velocity at contact
            dv = bodyRB.velocity + c->r2.cross(-bodyRB.angularVelocity) - bodyRA.velocity - c->r1.cross(-bodyRA.angularVelocity);

            Vec2d tangent = c->normal.cross(1.0f);
            float vt = dv.dot(tangent);
            float dPt = c->massTangent * (-vt);

            if (accumulateImpulses) {
                // Compute friction impulse
                float maxPt = friction * c->Pn;

                // Clamp friction
                float oldTangentImpulse = c->Pt;
                c->Pt = clamp(oldTangentImpulse + dPt, -maxPt, maxPt);
                dPt = c->Pt - oldTangentImpulse;
            } else {
                float maxPt = friction * dPn;
                dPt = clamp(dPt, -maxPt, maxPt);
            }

            // Apply contact impulse
            Vec2d Pt = tangent * dPt;

            bodyRA.velocity -= Pt * bodyRA.invMass;
            bodyRA.angularVelocity -= bodyRA.invI * c->r1.cross(Pt);

            bodyRB.velocity += Pt * bodyRB.invMass;
            bodyRB.angularVelocity += bodyRB.invI * c->r2.cross(Pt);
        }
    }

    Contact contacts[MAX_POINTS];
    int numContacts;

    ecs::Entity entity1;
    ecs::Entity entity2;

    // Combined friction
    float friction;
};

} // namespace ve

#endif /* !ARBITER_HPP_ */
