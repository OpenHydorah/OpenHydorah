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

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>
#include "init.h"
#include "cleanup.h"

#ifdef _WIN32
int CALLBACK WinMain(
		HINSTANCE hInst,
		HINSTANCE hPrevInst,
		LPSTR lpCmdLine,
		int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (InitSDL(&window, &renderer, 600, 480) != 0) {
		CleanSDL(window, renderer);
		return 1;
	}

	int running = 1;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	CleanSDL(window, renderer);

	return 0;
}
