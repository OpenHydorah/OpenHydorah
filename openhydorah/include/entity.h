/**
 * \file entity.h
 */

#ifndef OPENHYDORAH_OBJECT_H
#define OPENHYDORAH_OBJECT_H

#include "sprite.h"
#include <SDL.h>
#include <jansson.h>
#include "list.h"
#include "vector.h"
#include "property.h"
#include "collision.h"

/**
 * \struct entity
 *
 * An entity is a game object that has a
 * sprite, collision data and a location in the game.
 *
 * Entities are organized in a hierarchy, so that any
 * entity can have a number of children and siblings.
 *
 * For example, an enemy in the game could consist of
 * a root entity that is the body, and two child entities
 * that are its weapons.
 *
 * Each of the entities should be able to move independently,
 * but child entities inherit transformation data from their
 * parents.
 */
struct entity {
	struct sprite *sprite;
	char *name;
	struct vec2 position;
	struct entity *parent;

	struct list children;
	struct list branch;
	struct list properties;
	struct list col_objs;
};

/**
 * \param[in] sprite The entity's sprite
 * \param[in] name The entity's name.
 * Pass NULL if you don't intend to search for it
 * \param[in] parent The entity's parent
 * \param[in] children The entity's children
 *
 * \returns Pointer to the new entity. NULL if error.
 */
struct entity *entity_create(struct sprite *sprite, const char *name,
		struct entity *parent
		);

/**
 * \brief Creates an entity from a JSON object
 *
 * \param[in] root The JSON object
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The entity's parent
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new Object or NULL on error.
 */
struct entity *entity_create_json(json_t *root, struct list *textures,
		struct entity *parent, SDL_Renderer *renderer);

/**
 * \brief Creates a entity hierarchy from a JSON array
 *
 * \param[out] ent_list The list to add the created entities to
 * \param[in] root The JSON array
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The entity's parent
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return 0 on success, non-zero on failure.
 */
uint8_t entity_list_create_json(struct list *ent_list, json_t *root,
		struct list *textures, struct entity *parent,
		SDL_Renderer *renderer);

/**
 * \brief Creates an entity from a file
 *
 * \param[in] filename Path to the file to read
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The entity's parent
 * \param[in] renderer The renderer to use for texture loading
 *
 * \return The new entity
 */
struct entity *entity_create_file(const char *filename,
		struct list *textures, struct entity *parent,
		SDL_Renderer *renderer);

/**
 *
 * \param[in] entity The entity to draw
 * \param[in] renderer The renderer to use
 */
void entity_draw(struct entity *entity, SDL_Renderer *renderer);

/**
 *
 * Destroys the entity and its children.
 * Not its siblings.
 *
 * \param[in] entity The entity to destroy
 */
void entity_destroy(struct entity *entity);

/**
 * \brief Finds entities with name
 *
 * \param[in] entities The entity list to search through
 * \param[in] name The name to search for
 *
 * \return The entities with \em name.
 */
struct list entity_list_find(struct list entities, const char *name);

/**
 * \brief Finds first entity with name
 *
 * \param[in] entities The entity list to search through
 * \param[in] name The name to search for
 *
 * \return The first entity with \em name or NULL if not found.
 */
struct entity *entity_list_find_first(struct list *entities, const char *name);

/* GETTERS */
struct sprite *entity_get_sprite(struct entity *entity);
const char *entity_get_name(struct entity *entity);
struct entity *entity_get_parent(struct entity *entity);
float entity_get_position_x(struct entity *entity);
float entity_get_position_y(struct entity *entity);
float entity_get_number_property(struct entity *ent, const char *name);
uint8_t entity_get_bool_property(struct entity *ent, const char *name);
const char *entity_get_string_property(struct entity *ent, const char *name);
struct list *entity_get_collision_objects(struct entity *ent);

/* SETTERS */
void entity_set_position_x(struct entity *entity, float x);
void entity_set_position_y(struct entity *entity, float y);
void entity_set_number_property(struct entity *ent, float value, const char *name);
void entity_set_bool_property(struct entity *ent, uint8_t value, const char *name);
void entity_set_string_property(struct entity *ent, const char *value, const char *name);

#endif
