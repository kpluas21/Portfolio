#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Pong.h"
#include"Paddle.h"

int main(void) {
    GameManager* game = GameManager::Instance("Window", 640, 480, false);

    while(game->running()) {
        game->gameLoop();
    }

}