/**
 * \file texture.h
 */

#ifndef OPENHYDORAH_TEXTURE_H
#define OPENHYDORAH_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include "list.h"

/**
 * \struct texture
 *
 * A texture should represent visual data,
 * either from a file, or memory data.
 */
struct texture {
	SDL_Texture *ptr;
	uint32_t *ref_count;
	char *name;

	struct list list;
};

/**
 * \param[in] ptr The texture pointer
 * \param[in] name The texture name
 *
 * \return The new texture
 */
struct texture *texture_create(SDL_Texture *ptr, const char *name);

/**
 * \brief Creates a new texture using data from the specified file
 *
 * \param[in] filename The path to the file to read from
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new texture, or NULL if there was an error
 */
struct texture *texture_create_file(const char *filename, SDL_Renderer *renderer);

/**
 * \brief Copy a texture and increment the ref count
 *
 * \param[in] texture Texture to copy
 *
 * \return The new copy of the texture
 */
struct texture *texture_copy(struct texture *texture);

/**
 * \param[in] texture The texture to destroy
 */
void texture_destroy(struct texture *texture);

/**
 * \param[in] textures The texture list to destroy
 */
void texture_list_destroy(struct list *textures);

/**
 * \param[in] textures The texture list to search through
 * \param[in] name The name to search for
 *
 * \return The texture if found, NULL otherwise
 */
struct texture *texture_list_find(struct list *textures, const char *name);

#endif
