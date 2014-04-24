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

