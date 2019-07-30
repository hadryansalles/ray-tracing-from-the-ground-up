#include "../World/World.hpp"

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