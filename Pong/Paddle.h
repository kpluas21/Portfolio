#ifndef PADDLE_H
#define PADDLE_H

//Handles input , movement, physics and graphics for the paddles in the game
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class GameManager;

class Paddle {
public:
    //used to denote which paddle are we referring to 
    enum class Type{LEFT, RIGHT};

    //used to denote which direction is the paddle headed
    enum class Direction{UP, DOWN, NONE};

    Paddle(GameManager& parent, Type type, int x, int y);
    ~Paddle() = default;


    //self explanatory, takes some input, updates the positions,
    //then draws them to the renderer(screen)
    void handleInput();
    void update(double delta_time);
    void draw(SDL_Renderer** renderer);
private:
    //position and dimensions of the paddle
    int posx, posy;
    
    //movement speed of the paddle
    double moveSpeed = 50; 
    int velY = 10; //max vertical velocity
    
    //related to movement, this needs to be fixed...@!!!
    double m_y;

    //reference to the parent class to access the vector
    GameManager& pParent;

    Type      p_type;
    Direction p_direction;
    //TODO make a sdl rect struct here ONCE! Itll make the code much nicer.
    SDL_Rect position;
    //FIX INPUT!

    //debug: std::cerr current position 
    void displayPosition(Paddle& paddle);

};

#endif //PADDLE_H