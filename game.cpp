
#include "GameObject.h"
#include "game.h"
#include "tilemap.h"
GameObject* player;
GameObject* rin;
TileMap* tilemap;

int cnt = 0;

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){

}
Game::~Game(){

}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialized" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            std::cout << "Renderer created!" << std::endl;
        }
        
        isRunning = true;
    } 

    Entity playerEntity = Player("First_Player", 1);
    player = new GameObject("assets/sprites/male_mc/Male_Front_Nuetral.png", 0, 0);
    player->attachEntity(playerEntity);
    rin = new GameObject("assets/sprites/rin/Rin_Front_Nuetral.png", 100, 0);
    tilemap = new TileMap();
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update(){
    cnt++;
    std::cout << cnt << std::endl;
    player->Update();
    rin->Update();
}

void Game::render(){
    SDL_RenderClear(renderer);
    // this is where we add stuff to render
    tilemap->drawMap();
    player->Render();
    rin->Render();

    // this is where we add stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}