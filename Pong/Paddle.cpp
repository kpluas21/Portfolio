#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<vector>
#include"Paddle.h"
#include"Pong.h"


Paddle::Paddle(GameManager& parent, Type type, int x, int y) : pParent{parent} {
    //initial positions of the paddle
    posx = x; 
    posy = y;

    p_direction = Direction::NONE;
    p_type = type;
    m_y = static_cast<double>(posy);

    position.w = 50;
    position.h = 100;
}

void Paddle::draw(SDL_Renderer** renderer) {
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(*renderer, &position);
}

void Paddle::handleInput() {
    displayPosition(*this);
    Uint8 const *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_W] && p_type == Type::LEFT) {
        p_direction = Direction::UP;
    }
    else if(keys[SDL_SCANCODE_S] && p_type == Type::LEFT) {
        p_direction = Direction::DOWN;
    }
    if(keys[SDL_SCANCODE_UP] && p_type == Type::RIGHT) {
        p_direction = Direction::UP;
    }
    else if(keys[SDL_SCANCODE_DOWN] && p_type == Type::RIGHT) {
        p_direction = Direction::DOWN;
    }
}

void Paddle::update(double delta_time) {
    if(p_direction == Direction::UP) {
        if(position.y > 0) {
            position.y -= velY;
        }
    }
    else if (p_direction == Direction::DOWN) {
        if(position.y < 380) {
            position.y += velY;
        }
    }
    position.x = posx; 
}

void Paddle::displayPosition(Paddle& paddle) {
    if(p_type == Type::LEFT){std::cerr<<"LEFT\n";}
    else{std::cerr<<"RIGHT\n";}
    std::cerr<<"x: "<<paddle.position.x<<'\n';
    std::cerr<<"y: "<<paddle.position.y<<'\n';
    std::cerr<<"w: "<<paddle.position.w<<'\n';
    std::cerr<<"h: "<<paddle.position.h<<'\n';
    
}

        // switch(x.type) {

        //     //if a key was pressed...
        //     case SDL_KEYDOWN:
        //         //refer to the left paddle
        //         if(p_type == Type::LEFT) {
        //             if(keys[SDL_SCANCODE_W]) {
        //                 p_direction = Direction::UP;
        //             }
        //             else if(keys[SDL_SCANCODE_S]) {
        //                 p_direction = Direction::DOWN;
        //             }
        //         }
        //         //refer to the right paddle
        //         if(p_type == Type::RIGHT) {
        //             if(keys[SDL_SCANCODE_UP]) {
        //                 p_direction = Direction::UP;
        //             }
        //             else if(keys[SDL_SCANCODE_DOWN]) {
        //                 p_direction = Direction::DOWN;
        //             }
        //         }
        // }