#include "Window.hpp"

Window::Window(int width, int height) :
	pixels(width*height*4) {	
	w = width;
	h = height;
	running = false;
}

Window::~Window(){
	pixels.clear();
}

void Window::setPixel(int x, int y, int r, int g, int b){
	int pos = (w*4*y)+(x*4);
	pixels[pos+0] = b;
	pixels[pos+1] = g;
	pixels[pos+2] = r;
	pixels[pos+3] = SDL_ALPHA_OPAQUE;
}

void Window::update(){
	
}

bool Window::isOpen(){
	return running;
}