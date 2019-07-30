#include "Window-NOTHREAD.hpp"

Window_NOTHREAD::Window_NOTHREAD(int width, int height):
    Window(width, height) {
}

Window_NOTHREAD::~Window_NOTHREAD(){
	pixels.clear();
}

void Window_NOTHREAD::init(){
    window = SDL_CreateWindow("RTX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	w, h,SDL_WINDOW_SHOWN);
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, w, h);

    running = true;
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void Window_NOTHREAD::update(){

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    if(running && elapsed > 1.0f/60.0f){

        clock_gettime(CLOCK_MONOTONIC, &start);
        
        while( SDL_PollEvent( &event ) )
        {
            if( ( SDL_QUIT == event.type ) ||
                ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();	
                running = false;
                return;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, &pixels[0], w*4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}