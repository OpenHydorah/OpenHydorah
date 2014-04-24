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

int Initialize(SDL_Window** window, SDL_Renderer** renderer,
		const int width, const int height, char* argv[])
{
	if (InitSDL(window, renderer, width, height) != 0) {
		CleanSDL(*window, *renderer);
		return 1;
	}

	if (InitFS(argv[0]) != 0) {
		return 1;
	}

	return 0;
}
