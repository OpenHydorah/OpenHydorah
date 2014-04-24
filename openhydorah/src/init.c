/*
This file is part of OpenHydorah.

OpenHydorah is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenHydorah is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenHydorah.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "init.h"
#include "cleanup.h"
#include "physfs.h"

int InitSDL(SDL_Window** window, SDL_Renderer** renderer,
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

int Initialize(SDL_Window** window, SDL_Renderer** renderer,
		const int width, const int height, char* argv[])
{
	if (InitSDL(window, renderer, width, height) != 0) {
		CleanSDL(*window, *renderer);
		return 1;
	}

	PHYSFS_init(argv[0]);
	if (PHYSFS_mount("assets", NULL, 0) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/ folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	return 0;
}
