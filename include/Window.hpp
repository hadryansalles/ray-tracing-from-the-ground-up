#pragma once
#include <SDL2/SDL.h>

class Window{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event; 

public:
    Window(int width, int height);
    ~Window();

    void init();
    void putPixel(int x, int y, int* color);
    bool shouldClose();
    void close();
};