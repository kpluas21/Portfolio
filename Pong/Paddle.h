#ifndef PADDLE_H
#define PADDLE_H

//Handles input , movement, physics and graphics for the paddles in the game
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


class Paddle {
public:
    //used to denote which paddle are we referring to 
    enum class Type{LEFT, RIGHT};

    //used to denote which direction is the paddle headed
    enum class Direction{UP, DOWN, NONE};

    Paddle(Type type, int x, int y);
    ~Paddle() = default;


    //self explanatory, takes some input, updates the positions,
    //then draws them to the renderer(screen)
    void handleInput(SDL_Event const &event);
    void update(double delta_time);
    void draw(SDL_Renderer** renderer);
private:
    int posx, posy, posw, posh;
    double moveSpeed = 50; //pixels per frame
    
    double m_y;

    Type      p_type;
    Direction p_direction;
    //TODO make a sdl rect struct here ONCE!
    //FIX INPUT!
};

#endif //PADDLE_H