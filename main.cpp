// Last Changed on PC
#include <iostream>
#include <map>
#include <vector>
#include "entity.hpp"
#include "game.hpp"

Game *game = nullptr;

int main(int argc, char * argv[]){ 
    game = new Game();

    game-> init("Cursed - Version 0.0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()){

        game->handleEvents();
        game->update();
        game->render();
    }

    game ->clean();

    return 0;
}