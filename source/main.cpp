#include "../include/Window.hpp"

int main(){
    Window* main_window = new Window(800, 600);
    main_window->close();
    return 0;
}