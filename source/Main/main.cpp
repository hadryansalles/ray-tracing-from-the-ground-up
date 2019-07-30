#include "../World/World.hpp"

/* 
int main(){
    Window* main_window = new Window(800, 600);
    main_window->init();
    
    int r = 255;
    int g = 0;
    int b = 0;
    
    int i;
    for(i = 0; i < 600 && !main_window->shouldClose(); i++){
        main_window->setPixel(i, i, r, g, b);
        SDL_Delay(20);
    }
    while(!main_window->shouldClose()){
    }
    main_window->close();
    return 0;
}
*/

int main(){
    World w;
    w.build();
    if(w.tracer_ptr == NULL){
        printf("Tracer null. Aborting.\n");
        return 0;
    }
    w.render_scene();
    printf("Main thread terminated.\n");
    return 0;
}