#pragma once

#include "Window.hpp"
#include <thread>

class Window_THREAD : public Window {
public:
    Window_THREAD(int width, int height);
    ~Window_THREAD();

    void init();
};

void _windowThread(int width, int height, std::vector<unsigned char> *pixels, bool *running);