#pragma once

#include "entity.hpp"
#include "SDL2/SDL.h"
#include "texturemanager.h"

class GameObject{
    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();

        void attachEntity(Entity e);
        void Update();
        void Render();

    private:

        int xpos;
        int ypos;

        Entity entity;
        Player player;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
};