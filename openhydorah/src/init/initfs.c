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

int InitFS(const char* arg0)
{
	PHYSFS_init(arg0);
	if (PHYSFS_mount("assets", NULL, 0) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/ folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/graphics/sprites", "/graphics/sprites", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/graphics/sprites folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/graphics/backgrounds", "/graphics/backgrounds", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/graphics/backgrounds folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/fonts", "/fonts", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/fonts folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/sounds", "/sounds", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/sounds folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/musics", "/musics", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/musics folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/sprites", "/sprites", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/sprites folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	if (PHYSFS_mount("assets/mods", "/mods", 1) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Failed to mount assets/mods folder. %s\n",
				PHYSFS_getLastError()
				);

		return 1;
	}

	return 0;
}

