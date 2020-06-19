#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Transform.h"
#include "Input.h"
#include "Player.h"

Engine* Engine::s_Instance = nullptr;
Player* player=nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!=0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("SDLEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
    if(m_Window==nullptr){
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer==nullptr){
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }
    TextureManager::GetInstance()->Load("player_run","assets/run.png");
    TextureManager::GetInstance()->Load("player","assets/idle.png");
    player = new Player(new Properties("player",100,200,26,38));

    Transform tf;
    tf.Log();

    return m_IsRunning=true;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning=false;
}

void Engine::Update()
{
    player->Update(0);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer,123,218,254,255);
    SDL_RenderClear(m_Renderer);

    player->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
