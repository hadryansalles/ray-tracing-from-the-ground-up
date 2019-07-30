#include "Window-NOTHREAD.hpp"

Window_NOTHREAD::Window_NOTHREAD(int width, int height):
pixels(width*height*4){
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    running = false;
}

Window_NOTHREAD::~Window_NOTHREAD(){
    pixels.clear();
}

void Window_NOTHREAD::init(){
    window = SDL_CreateWindow("RTX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    running = true;
    frame_start = clock();
}

void Window_NOTHREAD::setPixel(int x, int y, int r, int g, int b){
	int pos = (SCREEN_WIDTH*4*y)+(x*4);
	pixels[pos+0] = b;
	pixels[pos+1] = g;
	pixels[pos+2] = r;
	pixels[pos+3] = SDL_ALPHA_OPAQUE;

    if((float)(frame_start-clock())/CLOCKS_PER_SEC > 1.0f/25.0f){
        frame_start = clock();
        updateVideo();
    }
}

bool Window_NOTHREAD::isOpen(){
    return running;
}

void Window_NOTHREAD::updateVideo(){
    if(running){
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
        SDL_UpdateTexture(texture, NULL, &pixels[0], SCREEN_WIDTH*4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}