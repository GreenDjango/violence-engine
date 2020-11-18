/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Joint
*/

#ifndef JOINT_HPP_
#define JOINT_HPP_

namespace ve {
/*
struct Joint {
    Joint() : P(0.0f, 0.0f),
              body1(0), body2(0),
              biasFactor(0.2f), softness(0.0f) {}

    void Set(RigidBody *body1, RigidBody *body2, const Vec2d &anchor) {
        body1 = b1;
        body2 = b2;

        Mat22 Rot1(body1->rotation);
        Mat22 Rot2(body2->rotation);
        Mat22 Rot1T = Rot1.Transpose();
        Mat22 Rot2T = Rot2.Transpose();

        localAnchor1 = Rot1T * (anchor - body1->position);
        localAnchor2 = Rot2T * (anchor - body2->position);

        P.Set(0.0f, 0.0f);

        softness = 0.0f;
        biasFactor = 0.2f;
    }

    void PreStep(float inv_dt) {
        // Pre-compute anchors, mass matrix, and bias.
        Mat22 Rot1(body1->rotation);
        Mat22 Rot2(body2->rotation);

        r1 = Rot1 * localAnchor1;
        r2 = Rot2 * localAnchor2;

        // deltaV = deltaV0 + K * impulse
        // invM = [(1/m1 + 1/m2) * eye(2) - skew(r1) * invI1 * skew(r1) - skew(r2) * invI2 * skew(r2)]
        //      = [1/m1+1/m2     0    ] + invI1 * [r1.y*r1.y -r1.x*r1.y] + invI2 * [r1.y*r1.y -r1.x*r1.y]
        //        [    0     1/m1+1/m2]           [-r1.x*r1.y r1.x*r1.x]           [-r1.x*r1.y r1.x*r1.x]
        Mat22 K1;
        K1.col1.x = body1->invMass + body2->invMass;
        K1.col2.x = 0.0f;
        K1.col1.y = 0.0f;
        K1.col2.y = body1->invMass + body2->invMass;

        Mat22 K2;
        K2.col1.x = body1->invI * r1.y * r1.y;
        K2.col2.x = -body1->invI * r1.x * r1.y;
        K2.col1.y = -body1->invI * r1.x * r1.y;
        K2.col2.y = body1->invI * r1.x * r1.x;

        Mat22 K3;
        K3.col1.x = body2->invI * r2.y * r2.y;
        K3.col2.x = -body2->invI * r2.x * r2.y;
        K3.col1.y = -body2->invI * r2.x * r2.y;
        K3.col2.y = body2->invI * r2.x * r2.x;

        Mat22 K = K1 + K2 + K3;
        K.col1.x += softness;
        K.col2.y += softness;

        M = K.Invert();

        Vec2d p1 = body1->position + r1;
        Vec2d p2 = body2->position + r2;
        Vec2d dp = p2 - p1;

        if (World::positionCorrection) {
            bias = -biasFactor * inv_dt * dp;
        } else {
            bias.Set(0.0f, 0.0f);
        }

        if (World::warmStarting) {
            // Apply accumulated impulse.
            body1->velocity -= body1->invMass * P;
            body1->angularVelocity -= body1->invI * Cross(r1, P);

            body2->velocity += body2->invMass * P;
            body2->angularVelocity += body2->invI * Cross(r2, P);
        } else {
            P.Set(0.0f, 0.0f);
        }
    }
    void ApplyImpulse() {
        Vec2d dv = body2->velocity + Cross(body2->angularVelocity, r2) - body1->velocity - Cross(body1->angularVelocity, r1);

        Vec2d impulse;

        impulse = M * (bias - dv - softness * P);

        body1->velocity -= body1->invMass * impulse;
        body1->angularVelocity -= body1->invI * Cross(r1, impulse);

        body2->velocity += body2->invMass * impulse;
        body2->angularVelocity += body2->invI * Cross(r2, impulse);

        P += impulse;
    }

    //Mat22 M;
    Vec2d localAnchor1, localAnchor2;
    Vec2d r1, r2;
    Vec2d bias;
    Vec2d P; // accumulated impulse
    RigidBody *body1;
    RigidBody *body2;
    float biasFactor;
    float softness;
};
*/

} // namespace ve

#endif /* !JOINT_HPP_ */
