#include <SDL2/SDL.h>

#ifndef __SDL_FUNCTIONS_H__
#define __SDL_FUNCTIONS_H__

inline extern void quitSDL(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

#endif