#include "mod.h"

#include <SDL.h>
#include <SDL_loadso.h>
#include <physfs.h>
#include <stdio.h>

struct mod_info *mod_info_get(const char *filename)
{
	struct mod_info *info = NULL;
	struct mod *mod = NULL;
	void *mod_handle = NULL;
	size_t len = strlen(filename);
	void (*get_info)(char**, char**) = NULL;

	const char *path = PHYSFS_getRealDir(filename);
	char *fullpath = malloc(len + strlen(path) + 2);
	sprintf(fullpath, "%s/%s", path, filename);

	mod_handle = SDL_LoadObject(fullpath);
	if (mod_handle == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				fullpath, SDL_GetError()
				);
		free (fullpath);
		return NULL;
	}

	get_info = SDL_LoadFunction(mod_handle, "get_info");
	if (get_info == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load mod '%s' - Error: %s",
				fullpath, SDL_GetError()
				);
		SDL_UnloadObject(mod_handle);
		free(fullpath);
		return NULL;
	}
	free(fullpath);

	char* name = NULL;
	char* desc = NULL;
	get_info(&name, &desc);

	info = malloc(sizeof(*info));
	info->filename = malloc(len + 1);
	strcpy(info->filename, filename);

	info->handle = mod_handle;

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

void mod_info_destroy(struct mod_info *info)
{
	if (info == NULL) return;

	SDL_UnloadObject(info->handle);
	free(info->name);
	free(info->description);
	free(info->filename);
	free(info);
}

struct mod *mod_create(struct mod_info *info)
{
	if (info == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"mod_info is NULL"
				);
		return NULL;
	}

	struct mod *mod = NULL;

	mod = malloc(sizeof(*mod));
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
	mod->init = SDL_LoadFunction(mod->info->handle, "mod_init");
	mod->update = SDL_LoadFunction(mod->info->handle, "mod_update");
	mod->destroy = SDL_LoadFunction(mod->info->handle, "mod_destroy");

	return mod;
}

void mod_destroy(struct mod *mod)
{
	if (mod == NULL) return;

	SDL_Log("Destroying mod: '%s'", mod->info->name);

	mod_info_destroy(mod->info);
	free(mod);
}
