#include "../Window/Window.hpp"

int main(){
    Window* main_window = new Window(800, 600);
    main_window->init();
    
    RGBColor red;
    red.r = 255;
    red.g = 0;
    red.b = 0;
    
    int i;
    for(i = 0; i < 600 && !main_window->shouldClose(); i++){
        main_window->putPixel(i, i, red);
        SDL_Delay(20);
    }
    while(!main_window->shouldClose()){
    }
    main_window->close();
    return 0;
}