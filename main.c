#include "window.c"
#include "keyloop.c"
#include "renderer.c"
#include <dirent.h>
#include <stdio.h>

SDL_Window *window;
SDL_Event event;
SDL_Renderer *renderer;

int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Specify filename\n");
		return 1;
	}else{
	initSDL(window);

	window = createWindow(window, renderer);

	renderer = SDL_CreateRenderer(window, -1, 0);

	while (1) {
		keyLoop(window, event);
		windowRenderer(window, renderer, argv[1]);
	}

	quitSDL(window);
	return 0;

	}
}