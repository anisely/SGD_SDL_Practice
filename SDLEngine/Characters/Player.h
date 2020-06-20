#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

class Player: public Character{

    public:
        Player(Properties* props);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        bool m_IsJumping;
        bool m_IsGrounded;

        float m_JumpTime;
        float m_JumpForce; //Hahahaha Jumpforce my sense of humor is a mystery

        Collider* m_Collider;
        Vector2D m_LastSafePosition;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

};


#endif // PLAYER_H
