#include "texture.h"
#include "globals.h"
#include <string.h>
#include <physfs.h>

TextureList* CreateTextureList(void)
{
	TextureList* list = malloc(sizeof(TextureList));
	list->texture = NULL;
	list->next = NULL;
	list->name = NULL;

	return list;
}

void AddTextureToList(TextureList** list, const char* name, Texture* texture)
{
	if (list == NULL) return;

	while (*list != NULL)
		*list = (*list)->next;

	(*list) = CreateTextureList();
	(*list)->texture = texture;
	size_t len = strlen(name);
	(*list)->name = malloc(len);
	strcpy((*list)->name, name);
}

Texture* GetTextureFromList(TextureList* list, const char* name)
{
	while (list != NULL)
	{
		if (strcmp(list->name, name) == 0)
		{
			return list->texture;
		}

		list = list->next;
	}

	return NULL;
}

Texture* CreateTextureFromFile(const char* filename)
{
	Texture* tex = NULL;
	PHYSFS_File* file = NULL;
	PHYSFS_sint64 fileLength = 0;
	uint8_t* buf = NULL;
	SDL_RWops* ops = NULL;

	if (PHYSFS_exists(filename) == 0)
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find texture '%s'",
				filename
				);
		return NULL;
	}

	file = PHYSFS_openRead(filename);
	fileLength = PHYSFS_fileLength(file);
	buf = malloc(fileLength);
	if (buf == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_SYSTEM,
				"Failed to allocate data for texture '%s'",
				filename
				);
		return NULL;
	}
	SDL_Log("Reading texture - %s - size: %i", filename,fileLength);
	PHYSFS_read(file, buf, 1, fileLength);
	PHYSFS_close(file);
	ops = SDL_RWFromMem(buf, fileLength);
	tex = IMG_LoadTexture_RW(g_renderer,ops,0);
	free(buf);
	SDL_RWclose(ops);

	return tex;
}

void DestroyTexture(Texture* texture)
{
	SDL_Log("Destroying texture.");
	SDL_DestroyTexture(texture);
}

void DestroyTextureList(TextureList* list)
{
	while (list != NULL)
	{
		TextureList* temp = list;
		list = list->next;
		DestroyTexture(temp->texture);
		free(temp->name);
		free(temp);
	}
}
