#include "Window.hpp"

Window::Window(int width, int height):
	pixels(width*height*4) {
	w = width;
	h = height;
	running = true;
}

Window::~Window(){
}

void Window::init(){
	std::thread video(windowThread, w, h, &pixels, &running);
	video.detach();
}

void Window::setPixel(int x, int y, int r, int g, int b){
	int pos = (w*4*y)+(x*4);
	pixels[pos+0] = b;
	pixels[pos+1] = g;
	pixels[pos+2] = r;
	pixels[pos+3] = SDL_ALPHA_OPAQUE;
}

bool Window::shouldClose(){
	return !running;
}

void windowThread(int width, int height, std::vector<unsigned char> *pixels, bool *running){
	
	int SCREEN_WIDTH = width;
    int SCREEN_HEIGHT = height;
    
	SDL_Window* window = SDL_CreateWindow("RTX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    
	SDL_Event event; 
    
	clock_t frame_start = clock();

	while(*running){
		if((double)(clock() - frame_start)/CLOCKS_PER_SEC > 1.0/60.0){
			frame_start = clock();
			while( SDL_PollEvent( &event ) )
			{
				if( ( SDL_QUIT == event.type ) ||
					( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
				{
					(*running) = false;
					break;
				}
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_UpdateTexture(texture, NULL, &(*pixels)[0], SCREEN_WIDTH*4);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}