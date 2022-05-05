#ifndef PONG_H
#define PONG_H
#include<SDL2/SDL.h>

//We will be using a singleton pattern for our main game class. This class will handle the one window and renderer, as well as the event loop.
//This ensures that the game cant be instanced a second time.

// class Paddle;

class GameManager {
public:
    static GameManager* Instance(const char* title, const int width, const int height, bool fullscreen);
    ~GameManager();

    //the existing interface goes here
    void gameLoop();
    //void update();
    bool running() const;
protected:
    GameManager(const char* title, const int width, const int height, bool fullscreen);
private:
    static GameManager* _instance;
    
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Event     event;
    
    bool isRunning;

    void update();
    void draw();

    // Paddle leftP;
    // Paddle rightP;
};


//Handles input , movement, physics and graphics for the paddles in the game
class Paddle {
public:
    Paddle(int x, int y);

    void handleInput(SDL_Event const &event);
    void update(double delta_time);
    void draw();
private:
    int posx, posy, posw, posh;
};


#endif //PONG_H