#include "texture.h"
#include "globals.h"
#include <string.h>
#include <physfs.h>

struct texture *texture_create(SDL_Texture *ptr, const char *name)
{
	struct texture *tex = malloc(sizeof(*tex));
	tex->ptr = ptr;
	tex->name = malloc(strlen(name) + 1);
	strcpy(tex->name, name);
	tex->ref_count = malloc(sizeof(uint32_t));
	*tex->ref_count = 0;
	list_init(&tex->list);

	return tex;
}

struct texture *texture_create_file(const char *filename, SDL_Renderer *renderer)
{
	PHYSFS_sint64 file_length = 0;
	uint8_t *buf = NULL;
	SDL_RWops *ops = NULL;
	SDL_Texture *tex;

	if (PHYSFS_exists(filename) == 0) {
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find texture '%s'",
				filename
				);
		return NULL;
	}

	file_length = fs_read_buffer(filename, &buf);
	SDL_Log("Reading texture - %s - size: %i", filename, file_length);

	if (file_length == 0) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to read texture from file: '%s'\n",
				filename
				);
		return NULL;
	}

	ops = SDL_RWFromMem(buf, file_length);
	tex = IMG_LoadTexture_RW(renderer, ops, 0);
	free(buf);
	SDL_RWclose(ops);

	return texture_create(tex, filename);
}

struct texture *texture_copy(struct texture *texture)
{
	if (texture == NULL) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Trying to copy NULL pointer as texture"
				);
		return NULL;
	}

	struct texture *tex = malloc(sizeof(*tex));
	tex->ptr = texture->ptr;
	tex->ref_count = texture->ref_count;
	tex->name = texture->name;
	tex->list = texture->list;

	(*tex->ref_count) += 1;

	return tex;
}

void texture_destroy(struct texture *texture)
{
	if (texture == NULL)
		return;

	if (*(texture->ref_count) == 0) {
		SDL_Log("Destroying texture.");
		SDL_DestroyTexture(texture->ptr);
		free(texture->ref_count);
		free(texture->name);
		list_remove(&texture->list);
	} else
		*(texture->ref_count) -= 1;

	free(texture);
}

void texture_list_destroy(struct list *textures)
{
	if (textures == NULL)
		return;

	struct texture *iter;
	struct texture *next;
	list_for_each_entry_safe(iter, next, textures, list)
	{
		texture_destroy(iter);
	}
}

struct texture *texture_list_find(struct list *textures, const char *name)
{
	struct texture *iter;
	list_for_each_entry(iter, textures, list)
	{
		if (strcmp(iter->name, name) == 0)
			return iter;
	}

	return NULL;
}
