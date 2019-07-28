#pragma once
#include <SDL2/SDL.h>

class Window{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Surface* screenSurface;

public:
    Window(int width, int height);
    ~Window();
    void close();
};