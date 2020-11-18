/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** CollisionSystem
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include "VE/Ecs.hpp"
#include "VE/Ecs/components/RigidBody.hpp"
#include "VE/Ecs/components/Transform.hpp"
#include "VE/Ecs/systems/CollisionSystem/Contact.hpp"
#include "VE/Maths/Mat22.hpp"

// Box vertex and edge numbering:
//
//        ^ y
//        |
//        e1
//   v2 ------ v1
//    |        |
// e2 |        | e4  --> x
//    |        |
//   v3 ------ v4
//        e3

namespace ve {

struct ClipVertex {
    ClipVertex() { fp.value = 0; }
    Vec2d v;
    FeaturePair fp;
};

struct Collider {

    enum Axis {
        FACE_A_X,
        FACE_A_Y,
        FACE_B_X,
        FACE_B_Y
    };

    enum EdgeNumbers {
        NO_EDGE = 0,
        EDGE1,
        EDGE2,
        EDGE3,
        EDGE4
    };

    // The normal points from A to B
    static int collide(Contact *contacts, Coordinator &ecs, ecs::Entity entityA, ecs::Entity entityB) {

        auto &bodyTA = ecs.getComponent<Transform>(entityA);
        auto &bodyTB = ecs.getComponent<Transform>(entityB);
        auto &bodyRA = ecs.getComponent<RigidBody>(entityA);
        auto &bodyRB = ecs.getComponent<RigidBody>(entityB);

        // Setup
        Vec2d hA = { 0.5f * bodyRA.width.x, 0.5f * bodyRA.width.y };
        Vec2d hB = { 0.5f * bodyRB.width.x, 0.5f * bodyRB.width.y };

        Vec2d posA = { bodyTA.pos.x + bodyRA.pos.x + hA.x, bodyTA.pos.y + bodyRA.pos.y + hA.y };
        Vec2d posB = { bodyTB.pos.x + bodyRB.pos.x + hB.x, bodyTB.pos.y + bodyRB.pos.y + hB.y };

        Mat22 RotA(bodyTA.rot);
        Mat22 RotB(bodyTB.rot);

        Mat22 RotAT = RotA.transpose();
        Mat22 RotBT = RotB.transpose();

        Vec2d dp = posB - posA;
        Vec2d dA = RotAT * dp;
        Vec2d dB = RotBT * dp;

        Mat22 C = RotAT * RotB;
        Mat22 absC = C.abs();
        Mat22 absCT = absC.transpose();

        // Box A faces
        Vec2d faceA = dA.abs() - hA - absC * hB;
        if (faceA.x > 0.0f || faceA.y > 0.0f)
            return 0;

        // Box B faces
        Vec2d faceB = dB.abs() - absCT * hA - hB;
        if (faceB.x > 0.0f || faceB.y > 0.0f)
            return 0;

        // Find best axis
        Axis axis;
        float separation;
        Vec2d normal;

        // Box A faces
        axis = FACE_A_X;
        separation = faceA.x;
        normal = dA.x > 0.0f ? RotA.col1 : -RotA.col1;

        const float relativeTol = 0.95f;
        const float absoluteTol = 0.01f;

        if (faceA.y > relativeTol * separation + absoluteTol * hA.y) {
            axis = FACE_A_Y;
            separation = faceA.y;
            normal = dA.y > 0.0f ? RotA.col2 : -RotA.col2;
        }

        // Box B faces
        if (faceB.x > relativeTol * separation + absoluteTol * hB.x) {
            axis = FACE_B_X;
            separation = faceB.x;
            normal = dB.x > 0.0f ? RotB.col1 : -RotB.col1;
        }

        if (faceB.y > relativeTol * separation + absoluteTol * hB.y) {
            axis = FACE_B_Y;
            separation = faceB.y;
            normal = dB.y > 0.0f ? RotB.col2 : -RotB.col2;
        }

        // Setup clipping plane data based on the separating axis
        Vec2d frontNormal, sideNormal;
        ClipVertex incidentEdge[2];
        float front, negSide, posSide;
        char negEdge, posEdge;

        // Compute the clipping lines and the line segment to be clipped.
        switch (axis) {
        case FACE_A_X: {
            frontNormal = normal;
            front = posA.dot(frontNormal) + hA.x;
            sideNormal = RotA.col2;
            float side = posA.dot(sideNormal);
            negSide = -side + hA.y;
            posSide = side + hA.y;
            negEdge = EDGE3;
            posEdge = EDGE1;
            computeIncidentEdge(incidentEdge, hB, posB, RotB, frontNormal);
        } break;
        case FACE_A_Y: {
            frontNormal = normal;
            front = posA.dot(frontNormal) + hA.y;
            sideNormal = RotA.col1;
            float side = posA.dot(sideNormal);
            negSide = -side + hA.x;
            posSide = side + hA.x;
            negEdge = EDGE2;
            posEdge = EDGE4;
            computeIncidentEdge(incidentEdge, hB, posB, RotB, frontNormal);
        } break;
        case FACE_B_X: {
            frontNormal = -normal;
            front = posB.dot(frontNormal) + hB.x;
            sideNormal = RotB.col2;
            float side = posB.dot(sideNormal);
            negSide = -side + hB.y;
            posSide = side + hB.y;
            negEdge = EDGE3;
            posEdge = EDGE1;
            computeIncidentEdge(incidentEdge, hA, posA, RotA, frontNormal);
        } break;
        case FACE_B_Y: {
            frontNormal = -normal;
            front = posB.dot(frontNormal) + hB.y;
            sideNormal = RotB.col1;
            float side = posB.dot(sideNormal);
            negSide = -side + hB.x;
            posSide = side + hB.x;
            negEdge = EDGE2;
            posEdge = EDGE4;
            computeIncidentEdge(incidentEdge, hA, posA, RotA, frontNormal);
        } break;
        }

        // clip other face with 5 box planes (1 face plane, 4 edge planes)

        ClipVertex clipPoints1[2];
        ClipVertex clipPoints2[2];
        int np;

        // Clip to box side 1
        np = clipSegmentToLine(clipPoints1, incidentEdge, -sideNormal, negSide, negEdge);

        if (np < 2)
            return 0;

        // Clip to negative box side 1
        np = clipSegmentToLine(clipPoints2, clipPoints1, sideNormal, posSide, posEdge);

        if (np < 2)
            return 0;

        // Now clipPoints2 contains the clipping points.
        // Due to roundoff, it is possible that clipping removes all points.

        int numContacts = 0;
        for (int i = 0; i < 2; ++i) {
            float separation = frontNormal.dot(clipPoints2[i].v) - front;

            if (separation <= 0) {
                contacts[numContacts].separation = separation;
                contacts[numContacts].normal = normal;
                // slide contact point onto reference face (easy to cull)
                contacts[numContacts].position = clipPoints2[i].v - frontNormal * separation;
                contacts[numContacts].feature = clipPoints2[i].fp;
                if (axis == FACE_B_X || axis == FACE_B_Y)
                    flipFeaturePair(contacts[numContacts].feature);
                ++numContacts;
            }
        }
        return numContacts;
    }

    static int clipSegmentToLine(ClipVertex vOut[2], ClipVertex vIn[2],
                                 const Vec2d &normal, float offset, char clipEdge) {
        // Start with no output points
        int numOut = 0;

        // Calculate the distance of end points to the line
        float distance0 = normal.dot(vIn[0].v) - offset;
        float distance1 = normal.dot(vIn[1].v) - offset;

        // If the points are behind the plane
        if (distance0 <= 0.0f) vOut[numOut++] = vIn[0];
        if (distance1 <= 0.0f) vOut[numOut++] = vIn[1];

        // If the points are on different sides of the plane
        if (distance0 * distance1 < 0.0f) {
            // Find intersection point of edge and plane
            float interp = distance0 / (distance0 - distance1);
            vOut[numOut].v = vIn[0].v + (vIn[1].v - vIn[0].v) * interp;
            if (distance0 > 0.0f) {
                vOut[numOut].fp = vIn[0].fp;
                vOut[numOut].fp.e.inEdge1 = clipEdge;
                vOut[numOut].fp.e.inEdge2 = NO_EDGE;
            } else {
                vOut[numOut].fp = vIn[1].fp;
                vOut[numOut].fp.e.outEdge1 = clipEdge;
                vOut[numOut].fp.e.outEdge2 = NO_EDGE;
            }
            ++numOut;
        }

        return numOut;
    }

    static void computeIncidentEdge(ClipVertex c[2], const Vec2d &h, const Vec2d &pos,
                                    const Mat22 &Rot, const Vec2d &normal) {
        // The normal is from the reference box. Convert it
        // to the incident boxe's frame and flip sign.
        Mat22 RotT = Rot.transpose();
        Vec2d n = -(RotT * normal);
        Vec2d nAbs = n.abs();

        if (nAbs.x > nAbs.y) {
            if (n.x >= 0.0f) {
                c[0].v = { h.x, -h.y };
                c[0].fp.e.inEdge2 = EDGE3;
                c[0].fp.e.outEdge2 = EDGE4;

                c[1].v = { h.x, h.y };
                c[1].fp.e.inEdge2 = EDGE4;
                c[1].fp.e.outEdge2 = EDGE1;
            } else {
                c[0].v = { -h.x, h.y };
                c[0].fp.e.inEdge2 = EDGE1;
                c[0].fp.e.outEdge2 = EDGE2;

                c[1].v = { -h.x, -h.y };
                c[1].fp.e.inEdge2 = EDGE2;
                c[1].fp.e.outEdge2 = EDGE3;
            }
        } else {
            if (n.y >= 0.0f) {
                c[0].v = { h.x, h.y };
                c[0].fp.e.inEdge2 = EDGE4;
                c[0].fp.e.outEdge2 = EDGE1;

                c[1].v = { -h.x, h.y };
                c[1].fp.e.inEdge2 = EDGE1;
                c[1].fp.e.outEdge2 = EDGE2;
            } else {
                c[0].v = { -h.x, -h.y };
                c[0].fp.e.inEdge2 = EDGE2;
                c[0].fp.e.outEdge2 = EDGE3;

                c[1].v = { h.x, -h.y };
                c[1].fp.e.inEdge2 = EDGE3;
                c[1].fp.e.outEdge2 = EDGE4;
            }
        }
        c[0].v = pos + Rot * c[0].v;
        c[1].v = pos + Rot * c[1].v;
    }

    static void flipFeaturePair(FeaturePair &fp) {
        std::swap(fp.e.inEdge1, fp.e.inEdge2);
        std::swap(fp.e.outEdge1, fp.e.outEdge2);
    };
};

} // namespace ve

#endif /* !COLLIDER_HPP_ */
