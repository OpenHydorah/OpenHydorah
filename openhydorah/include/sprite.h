/**
 * \file sprite.h
 */

#ifndef OPENHYDORAH_SPRITE_H
#define OPENHYDORAH_SPRITE_H

#include <SDL.h>
#include <stdint.h>
#include "texture.h"
#include "frame.h"
#include "animation.h"
#include <jansson.h>

/**
 * \struct sprite
 *
 * A sprite is a texture with a number
 * of frames and animations.
 */
struct sprite {
	struct texture *texture;
	struct frame **frames;
	struct animation **animations;
	uint32_t num_frames;
	uint32_t num_animations;

	struct list list;
};

/**
 * \param[in] texture The sprite's texture
 * \param[in] frames The sprite's frames
 * \param[in] defaultFrame The frame to use by default.
 * If NULL, then it's the first in \em frames
 * \param[in] animations The sprite's animations
 *
 * \return The new sprite or NULL on error.
 */
struct sprite *sprite_create(struct texture *texture, struct frame **frames,
		uint32_t num_frames, struct animation **animations,
		uint32_t num_animations);

/**
 * \brief Creates a sprite from a JSON object
 *
 * \param[in] root The JSON object
 * \param[out] textures The list to add the sprite textures to
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new sprite or NULL on error
 */
struct sprite *sprite_create_json(json_t *root, struct list *textures,
		SDL_Renderer *renderer);

/**
 * \brief Creates a sprite from a file
 *
 * \param[in] filename The file to read from
 * \param[out] textures The list to add the sprite textures to
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new sprite or NULL on error
 */
struct sprite *sprite_create_file(const char *filename, struct list *textures,
		SDL_Renderer *renderer);

/**
 * \param[in] sprite The sprite to destroy
 */
void sprite_destroy(struct sprite *sprite);

/**
 * \param[in] sprites The list of sprites to destroy
 */
void sprite_list_destroy(struct list *sprites);

/**
 * \brief Draws the sprite at the specified point
 *
 * \param[in] sprite Sprite to draw
 * \param[in] point The point to draw at
 * \param[in] renderer The renderer to use
 */
void sprite_draw_point(struct sprite *sprite, SDL_Point point,
		SDL_Renderer *renderer);

#endif
