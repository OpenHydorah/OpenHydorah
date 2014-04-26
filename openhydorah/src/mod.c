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

#include "mod.h"

#include <SDL.h>
#include <SDL_loadso.h>

Mod* LoadMod(const char* filename)
{
	ModInfo* info = NULL;
	Mod* mod = NULL;
	void* modHandle = SDL_LoadObject(filename);
	void (*getInfo)(char**, char**);
	if (modHandle == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				filename, SDL_GetError()
				);
		return NULL;
	}

	getInfo = SDL_LoadFunction(modHandle, "getInfo");
	if (getInfo == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				filename, SDL_GetError()
				);
		SDL_UnloadObject(modHandle);
		return NULL;
	}

	char* name = NULL;
	char* desc = NULL;
	getInfo(&name, &desc);

	info = malloc(sizeof(ModInfo));
	size_t len = strlen(name);
	info->name = malloc(len);
	strcpy(info->name, name);
	free(name);
	len = strlen(desc);
	info->description = malloc(len);
	strcpy(info->description, desc);
	free(desc);

	mod = malloc(sizeof(Mod));
	mod->info = info;
	mod->handle = modHandle;

	return mod;
}
