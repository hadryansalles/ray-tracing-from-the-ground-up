#pragma once

#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <thread>

class Window{
private:
    int w;
    int h;
    bool running;
    std::vector<unsigned char> pixels;
    
public:
    Window(int width, int height);
    ~Window();

    void init();
    void setPixel(int x, int y, int r, int g, int b);
    void updateVideo();
    bool shouldClose();
};

void windowThread(int width, int height, std::vector<unsigned char> *pixels, bool *running);