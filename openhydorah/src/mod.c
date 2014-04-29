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
	size_t len = strlen(filename);
	void (*getInfo)(char**, char**) = NULL;

	const char* path = PHYSFS_getRealDir(filename);
	char* fullpath = malloc(len + strlen(path) + 2);
	sprintf(fullpath, "%s/%s", path, filename);

	modHandle = SDL_LoadObject(fullpath);
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
	info->filename = malloc(len + 1);
	strcpy(info->filename, filename);

	info->handle = modHandle;

	len = strlen(name);
	info->name = malloc(len + 1);
	strcpy(info->name, name);
	free(name);

	len = strlen(desc);
	info->description = malloc(len + 1);
	strcpy(info->description, desc);
	free(desc);

	return info;
}

void DestroyModInfo(ModInfo* info)
{
	if (info == NULL) return;

	SDL_UnloadObject(info->handle);
	free(info->name);
	free(info->description);
	free(info->filename);
	free(info);
}

Mod* CreateMod(ModInfo* info)
{
	if (info == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"ModInfo is NULL"
				);
		return NULL;
	}

	Mod* mod = NULL;
	void (*modInit)(Mod*) = NULL;

	mod = malloc(sizeof(Mod));
	if (mod == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate memory for mod: '%s'",
				info->name
				);
		return NULL;
	}

	mod->info = info;
	modInit = SDL_LoadFunction(mod->info->handle, "modInit");

	if (modInit != NULL)
		modInit(mod);

	return mod;
}

void DestroyMod(Mod* mod)
{
	if (mod == NULL) return;
	void (*modDeinit)(Mod*) = SDL_LoadFunction(mod->info->handle, "modDeinit");

	SDL_Log("Destroying mod: '%s'", mod->info->name);

	if (modDeinit != NULL)
		modDeinit(mod);
	DestroyModInfo(mod->info);
	free(mod);
}
