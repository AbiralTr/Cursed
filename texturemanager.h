#include "SDL2/SDL.h"

class TextureManager{

    public:
        static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);


};