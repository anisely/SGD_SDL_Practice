#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Player::Player(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 4, 104, SDL_FLIP_HORIZONTAL);
}

void Player::Draw()
{

    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Player::Update(float dt)
{
    m_Animation->SetProps("player", 0, 4, 200);
    m_RigidBody->UnsetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
            //SDL_Log("A");
            m_RigidBody->ApplyForceX(10*BACKWARD);
            m_Animation->SetProps("player_run", 0, 17, 180, SDL_FLIP_HORIZONTAL);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
            //SDL_Log("D");
            m_RigidBody->ApplyForceX(10*FORWARD);
            m_Animation->SetProps("player_run", 0, 17, 180);
    }


    m_RigidBody->Update(0.3);
    //m_RigidBody->ApplyForceX(5);

    m_Transform->TranslateX(m_RigidBody->Position().X);
    //m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
