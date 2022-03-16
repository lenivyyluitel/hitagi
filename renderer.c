#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);

void windowRenderer(SDL_Window *window, SDL_Renderer *renderer, const char *file)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
}

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(file);
	if (surface) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}