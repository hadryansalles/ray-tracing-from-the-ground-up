#pragma once

#include <SDL2/SDL.h>
#include <time.h>
#include <vector>

class Window{
protected:
    int w;
    int h;
    bool running;
    std::vector<unsigned char> pixels;
    
public:
    Window(int width, int height);
    virtual ~Window();

    virtual void init() = 0;
    virtual void update();
    void setPixel(int x, int y, int r, int g, int b);
    bool isOpen();
};