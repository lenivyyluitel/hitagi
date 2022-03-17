#include "sdl_functions.h"
#include <string.h>

#define windowWidth 500
#define windowHeight 500

void initSDL(SDL_Window *window)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initalized %s\n", SDL_GetError());
		quitSDL(window);
	}
}

SDL_Window *createWindow(SDL_Window *window, SDL_Renderer *renderer, char *file)
{
	window = SDL_CreateWindow(file, SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, windowWidth,
				  windowHeight, SDL_WINDOW_RESIZABLE);
	if (!window) {
		printf("Window could not be created %s\n", SDL_GetError());
		quitSDL(window);
	}

	return window;
}
