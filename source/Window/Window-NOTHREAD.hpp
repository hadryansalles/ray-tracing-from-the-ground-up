#pragma once

#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <thread>

class Window_NOTHREAD{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
    clock_t frame_start;
    bool running;
    std::vector<unsigned char> pixels;

    void updateVideo();
    
public:
    Window_NOTHREAD(int width, int height);
    ~Window_NOTHREAD();

    void init();
    void setPixel(int x, int y, int r, int g, int b);
    bool isOpen();
}