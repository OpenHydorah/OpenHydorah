#include "mod.h"

#include <SDL.h>
#include <SDL_loadso.h>
#include <physfs.h>
#include <stdio.h>

ModInfo* GetModInfo(const char* filename)
{
	ModInfo* info = NULL;
	Mod* mod = NULL;
	void* modHandle = NULL;
	const char* path = PHYSFS_getRealDir(filename);
	char* fullpath = malloc(strlen(filename) + strlen(path) + 2);
	sprintf(fullpath, "%s/%s", path, filename);
	printf("path = %s\n", fullpath);
	modHandle = SDL_LoadObject(fullpath);
	void (*getInfo)(char**, char**);
	if (modHandle == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				fullpath, SDL_GetError()
				);
		free (fullpath);
		return NULL;
	}

	getInfo = SDL_LoadFunction(modHandle, "getInfo");
	if (getInfo == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				fullpath, SDL_GetError()
				);
		SDL_UnloadObject(modHandle);
		free(fullpath);
		return NULL;
	}
	free(fullpath);

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

	return info;
}
