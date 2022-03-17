#include <SDL2/SDL_image.h>
#include "gifdec.h"
#include "keyloop.c"

void renderImage(SDL_Window *window, SDL_Renderer *renderer, const char *file)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file);

	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

// https://github.com/lecram/gifdec/blob/master/example.c
void renderGif(SDL_Window *window, SDL_Renderer *renderer, const char *file)
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Event event;
	gd_GIF *gif;
	char title[32] = { 0 };
	Uint8 *color, *frame;
	void *addr;
	int i, j;
	Uint32 pixel;
	int ret, paused, quit;
	Uint32 t0, t1, delay, delta;

	gif = gd_open_gif(file);
	if (!gif) {
		fprintf(stderr, "Could not open %s\n", file);
		quitSDL(window);
	}
	frame = malloc(gif->width * gif->height * 3);
	if (!frame) {
		fprintf(stderr, "Could not allocate frame\n");
		quitSDL(window);
	}

	color = &gif->gct.colors[gif->bgindex * 3];
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0x00);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	surface = SDL_CreateRGBSurface(0, gif->width, gif->height, 32, 0, 0, 0,
				       0);
	if (!surface) {
		SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
		quitSDL(window);
	}
	while (1) {
		keyLoop(window, event);
		t0 = SDL_GetTicks();
		ret = gd_get_frame(gif);
		if (ret == -1)
			break;
		SDL_LockSurface(surface);
		gd_render_frame(gif, frame);
		color = frame;
		for (i = 0; i < gif->height; i++) {
			for (j = 0; j < gif->width; j++) {
				if (!gd_is_bgcolor(gif, color))
					pixel = SDL_MapRGB(surface->format,
							   color[0], color[1],
							   color[2]);
				else if (((i >> 2) + (j >> 2)) & 1)
					pixel = SDL_MapRGB(surface->format,
							   0x7F, 0x7F, 0x7F);
				else
					pixel = SDL_MapRGB(surface->format,
							   0x00, 0x00, 0x00);
				addr = surface->pixels +
				       (i * surface->pitch + j * sizeof(pixel));
				memcpy(addr, &pixel, sizeof(pixel));
				color += 3;
			}
		}
		SDL_UnlockSurface(surface);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(texture);
		t1 = SDL_GetTicks();
		delta = t1 - t0;
		delay = gif->gce.delay * 10;
		delay = delay > delta ? delay - delta : 1;
		SDL_Delay(delay);
		if (ret == 0)
			gd_rewind(gif);
	}
}

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF);
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(file);
	if (surface) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}