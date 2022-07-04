//The interface for our ball
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Ball {
public:
    Ball();
    ~Ball() = default;
    
    void update();
    void draw(SDL_Renderer** renderer);
private:
    SDL_Rect position;
};