#include "sdl_functions.h"
#include <SDL2/SDL_keycode.h>
#include <stdio.h>

int keyLoop(SDL_Window *window, SDL_Event event)
{
	while (SDL_PollEvent(&event)) {
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			printf("ESC pressed, closing window\n");
			quitSDL(window);
			break;
		case SDLK_q:
			printf("q pressed, closing window\n");
			quitSDL(window);
			break;
		default:
			break;
		}
	}
	return 0;
}
