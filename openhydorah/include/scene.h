/**
 * \file scene.h
 */

#ifndef OPENHYDORAH_SCENE_H
#define OPENHYDORAH_SCENE_H

#include "texture.h"
#include "list.h"
#include "entity.h"
#include "sprite.h"

/**
 * \struct scene
 *
 * A scene contains a collection of entities and sprites
 */
struct scene {
	struct list entities;
	struct list sprites;
};

/**
 * \return The new scene
 */
struct scene *scene_create(void);

/**
 * \brief Creates a new scene from a JSON object
 *
 * \param[in] root The JSON object
 * \param[out] textures The list to add the sprites' textures
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new scene
 */
struct scene *scene_create_json(json_t *root, struct list *textures,
		SDL_Renderer *renderer);

/**
 * \brief Creates a new scene from file
 *
 * \param[in] filename Path to file to read
 * \param[out] textures The list to add the sprites' textures
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new scene
 */
struct scene *scene_create_file(const char *filename, struct list *textures,
		SDL_Renderer *renderer);

/**
 * \brief Destroys the scene and its objects
 *
 * \param[in] scene The scene to destroy
 */
void scene_destroy(struct scene *scene);

/**
 * \brief Draws the scene
 *
 * This draws everything in the scene
 *
 * \param[in] scene The scene to draw
 * \param[in] renderer The renderer to use
 */
void scene_draw(struct scene *scene, SDL_Renderer *renderer);

/* GETTERS */
struct list *scene_get_entities(struct scene *scene);

#endif
