#include "Window.hpp"

Window::Window(int width, int height) {
	SCREEN_HEIGHT = height;
	SCREEN_WIDTH = width;
	window = NULL;
	renderer = NULL;
}

Window::~Window(){
}

void Window::init(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void Window::putPixel(int x, int y, RGBColor color){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_RenderPresent(renderer);
}

bool Window::shouldClose(){
	if(SDL_PollEvent(&event) && event.type == SDL_QUIT){
		return true;
	}
	return false;
}

void Window::close(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}