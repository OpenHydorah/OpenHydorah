#include "init.h"

int init_sdl(SDL_Window** window, SDL_Renderer** renderer,
		const int width, const int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Failed to initialize SDL: %s\n",
				SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow(
			"OpenHydorah - devel",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width, height,
			0);

	if (*window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
			"Failed to initialize SDL window: %s\n",
			SDL_GetError());
		return 1;
	}

	*renderer = SDL_CreateRenderer(*window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (*renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"Failed to initialize SDL renderer: %s\n",
			SDL_GetError());
		return 1;
	}

	return 0;
}

