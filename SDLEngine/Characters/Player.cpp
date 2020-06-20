#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"


Player::Player(Properties* props): Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 104, SDL_FLIP_HORIZONTAL);
}

void Player::Draw()
{

   m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

  // Vector2D cam = Camera::GetInstance()->GetPosition(); //Preview of the collision box
  // SDL_Rect box = m_Collider->Get();
  // box.x -=cam.X;
  // box.y -=cam.Y;
  // SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Player::Update(float dt)
{
    m_Animation->SetProps("player", 1, 4, 200);
    m_RigidBody->UnsetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
            SDL_Log("A");
            m_RigidBody->ApplyForceX(10*BACKWARD);
            m_Animation->SetProps("player_run", 1, 17, 60, SDL_FLIP_HORIZONTAL);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
            SDL_Log("D");
            m_RigidBody->ApplyForceX(10*FORWARD);
            m_Animation->SetProps("player_run", 1, 17, 60);
    }

    //JUMP JUMP JUMPING ALL AROUND
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded){
        m_IsJumping=true;
        m_IsGrounded=false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    //PRESSURE SENSITIVE JUMPS ON ANALOG KEYBOARDS????WITCHCRAFT
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{
        m_IsJumping=false;
        m_JumpTime=JUMP_TIME;
    }

    m_RigidBody->Update(dt);

    m_RigidBody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X,m_Transform->Y,32,32);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X=m_LastSafePosition.X;

    m_RigidBody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X,m_Transform->Y,32,32);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded=true;
        m_Transform->Y=m_LastSafePosition.Y;
    }else{
        m_IsGrounded=false;
    }


    if(m_IsJumping|| !m_IsGrounded)
                m_Animation->SetProps("player_jump", 1, 3, 1000);

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;


    m_Animation->Update();

}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
