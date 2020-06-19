#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.9f

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
    public:
        RigidBody() {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
        }

        inline void SetMass(float mass){m_Mass = mass;}
        inline void SetGravity(float gravity){m_Gravity = gravity;}
        inline void ApplyForce(Vector2D f){m_Force = f;}
        inline void ApplyForceX(float fx){m_Force.X = fx;}
        inline void ApplyForceY(float fy){m_Force.Y = fy;}
        inline void UnsetForce(){m_Force= Vector2D(0,0);}

        inline void ApplyFriction(Vector2D fr){m_Friction=fr;}
        inline void UnsetFriction(){m_Friction=Vector2D(0,0);}

        inline float GetMass(){return m_Mass;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Velocity(){return m_Velocity;}
        inline Vector2D Acceleration(){return m_Acceleration;}

        void Update(float dt){
            m_Acceleration.X = (m_Force.X + m_Friction.X)/m_Mass;
            m_Acceleration.Y = m_Gravity + m_Force.Y/m_Mass;
            m_Velocity= m_Acceleration*dt;
            m_Position= m_Velocity*dt;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;

};

#endif // RIGIDBODY_H
