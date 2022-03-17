#include "window.c"
#include "renderer.c"
#include <dirent.h>
#include <stdio.h>

SDL_Window *window;
SDL_Event event;
SDL_Renderer *renderer;

const char *checkGIF(const char *str)
{
	char result[4];
	for (int i = 0; i < 4; i++) {
		result[i] = str[strlen(str) - (3 - i)];
	}

	return &str[(strlen(str) - 3)];
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Specify filename\n");
		return 1;
	} else {
		initSDL(window);

		window = createWindow(window, renderer, argv[1]);

		printf("%s\n", checkGIF(argv[1]));

		renderer = SDL_CreateRenderer(window, -1, 0);

		while (1) {
			if (strcmp(checkGIF(argv[1]), "gif") == 0) {
				keyLoop(window, event);
				renderGif(window, renderer, argv[1]);
			} else {
				keyLoop(window, event);
				renderImage(window, renderer, argv[1]);
			}
		}

		quitSDL(window);
		return 0;
	}
}