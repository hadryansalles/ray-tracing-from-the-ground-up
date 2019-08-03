#include "../World/World.hpp"

int main(){
    World w;
    w.build();
    debug_print("Build finished.\n");
    if(w.tracer_ptr == NULL){
        printf("Tracer null. Aborting.\n");
        return 1;
    }
    if(w.camera == NULL){
        printf("Camera null. Aborting.\n");
        return 1;
    }
    w.camera->render_scene(w);
    debug_print("Main thread terminated.\n");
    return 0;
}