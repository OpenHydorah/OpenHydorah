#include "cleanup.h"
#include <physfs.h>

void CleanSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	if (window != NULL)
		SDL_DestroyWindow(window);

	SDL_Quit();
}

void Cleanup(SDL_Window* window, SDL_Renderer* renderer)
{
	CleanSDL(window, renderer);

	PHYSFS_deinit();
}

