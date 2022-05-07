#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Paddle.h"

Paddle::Paddle(Type type, int x, int y) {
    //initial positions of the paddle
    posx = x; 
    posy = y;

    //dimensions of the paddle
    posw = 50;
    posh = 100;

    p_direction = Direction::NONE;
    p_type = type;
    m_y = static_cast<double>(posy);

}

void Paddle::draw(SDL_Renderer** renderer) {
    SDL_Rect fillRect = {posx, posy, posw, posh};
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(*renderer, &fillRect);
}

void Paddle::handleInput(SDL_Event const &event) {

    
    
    switch(event.type) {
        //if a key was pressed...
        case SDL_KEYDOWN:
         Uint8 const *keys = SDL_GetKeyboardState(nullptr);
            //refer to the left paddle
            if(p_type == Type::LEFT) {
                if(keys[SDL_SCANCODE_W]) {
                    p_direction = Direction::UP;
                }
                else if(keys[SDL_SCANCODE_S]) {
                    p_direction = Direction::DOWN;
                }
            }
            //refer to the right paddle
            if(p_type == Type::RIGHT) {
                if(keys[SDL_SCANCODE_UP]) {
                    p_direction = Direction::UP;
                }
                else if(keys[SDL_SCANCODE_DOWN]) {
                    p_direction = Direction::DOWN;
                }
            }
    }
}

void Paddle::update(double delta_time) {
    if(p_direction == Direction::UP) {
        if(m_y > 0) {
            m_y -= delta_time * moveSpeed;
            posy = m_y;
        }
    }
    else if (p_direction == Direction::DOWN) {
        if(m_y < 380) {
            m_y += delta_time * moveSpeed;
            posy = m_y;
        }
    }
}