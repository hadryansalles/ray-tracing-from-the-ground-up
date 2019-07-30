#pragma once

#include "Window.hpp"

class Window_NOTHREAD : public Window{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
    struct timespec start, finish;
	double elapsed = 1000.0;
    
public:
    Window_NOTHREAD(int width, int height);
    ~Window_NOTHREAD();

    void init();
    void update();
};