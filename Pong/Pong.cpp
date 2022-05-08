//Implementation details for Pong.h/GameManager
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<vector>
#include"Pong.h"

//initialize the instance to 0.
GameManager* GameManager::_instance = 0;

GameManager* GameManager::Instance(const char* title, const int width, const int height, bool fullscreen) {
    if(_instance == 0) {
        _instance = new GameManager(title, width, height, fullscreen); 
    }
    return _instance;
}

//Initialize our windows, renderer, and the two paddles.
GameManager::GameManager(const char* title, const int width, const int height, bool fullscreen) 
    : leftP(*this, Paddle::Type (0), 0, (480 / 2) - 50) 
    , rightP(*this, Paddle::Type (1), 640 - 50, (480 / 2) - 50) {
        
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        throw std::bad_alloc();
    }

    Uint16 flags = fullscreen ? SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_ALLOW_HIGHDPI;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if(window == nullptr) {
        SDL_Log("Unable to create window %s", SDL_GetError());
        throw std::bad_alloc();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        SDL_Log("Unable to create renderer %s", SDL_GetError());
        throw std::bad_alloc();
    }

    //if all goes well, turn on isRunning
    isRunning = true;
}

GameManager::~GameManager() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    
    IMG_Quit();
    SDL_Quit();
}

bool GameManager::running() const {return isRunning;}

std::vector<SDL_Event>& GameManager::getFrameEvents() {
    static std::vector<SDL_Event> frameEvents;
    return frameEvents;
}

void GameManager::gameLoop() {
    //A very simply input, update, and render loop.
    handleInput();
    update();
    draw();    
}

void GameManager::handleInput() {
    while(SDL_PollEvent(&event) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
        }
        getFrameEvents().push_back(event);
    }
    
    leftP.handleInput(event);
    rightP.handleInput(event);

    getFrameEvents().clear();
}

void GameManager::update() {
    leftP.update(1.0/60.0);
    rightP.update(1.0/60.0);

}

void GameManager::draw() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

    SDL_RenderClear(renderer);

    leftP.draw(&renderer);
    rightP.draw(&renderer);
    SDL_RenderPresent(renderer);
}


















