#include "entity.h"

#include "filesystem.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct entity *entity_create(struct sprite *sprite, const char *name,
		struct entity *parent
		)
{
	struct entity *ent = malloc(sizeof(*ent));
	ent->sprite = sprite;
	if (name != NULL) {
		size_t len = strlen(name);
		ent->name = malloc(len + 1);
		strcpy(ent->name, name);
	} else
		ent->name = NULL;

	list_init(&ent->children);
	list_init(&ent->branch);
	list_init(&ent->properties);
	list_init(&ent->col_objs);

	ent->position.x = 0.0f;
	ent->position.y = 0.0f;
	ent->parent = parent;
	if (parent != NULL) {
		list_append(&ent->branch, &ent->parent->children);
	}

	return ent;
}

void entity_draw(struct entity *entity, SDL_Renderer *renderer)
{
	if (entity == NULL)
		return;

	SDL_Point position;
	position.x = round(entity->position.x);
	position.y = round(entity->position.y);
	sprite_draw_point(entity->sprite, position, renderer);

	struct entity *iter;

	list_for_each_entry(iter, &entity->children, children)
	{
		entity_draw(iter, renderer);
	}

	struct collision_object *col_iter;
	list_for_each_entry(col_iter, &entity->col_objs, list)
	{
		collision_object_draw(col_iter, renderer);
	}
}

void entity_destroy(struct entity *entity)
{
	if (entity == NULL)
		return;

	struct entity *child_iter;
	struct entity *child_next;
	list_for_each_entry_safe(child_iter, child_next, &entity->children, branch)
	{
		entity_destroy(child_iter);
	}

	struct property *p_iter;
	struct property *p_next;
	list_for_each_entry_safe(p_iter, p_next, &entity->properties, list)
	{
		property_destroy(p_iter);
	}

	struct collision_object *col_iter;
	struct collision_object *col_next;
	list_for_each_entry_safe(col_iter, col_next, &entity->col_objs, list)
	{
		collision_object_destroy(col_iter);
	}

	sprite_destroy(entity->sprite);
	free(entity->name);
	free(entity);
}

uint8_t entity_list_create_json(struct list *ent_list, json_t *root,
		struct list *textures, struct entity *parent, SDL_Renderer *renderer)
{
	if (!json_is_array(root)) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Can't create entities. JSON is not array."
				);
		return 1;
	}

	uint32_t i = 0;
	struct entity *ent;
	json_t *arr_json = NULL;
	json_t *obj_json = NULL;

	for (i = 0; i < json_array_size(root); i++) {
		struct vec2 position = {0, };

		arr_json = json_array_get(root, i);
		if (!json_is_object(arr_json)) {
			SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"Element in entity array is not JSON object."
					);
			continue;
		}

		obj_json = json_object_get(arr_json, "entity");
		if (json_is_string(obj_json)) {
			ent = entity_create_file(json_string_value(obj_json),
						textures, parent, renderer);

			list_append(&ent->branch, ent_list);
		} else if (json_is_object(obj_json)) {
			ent = entity_create_json(obj_json,
					textures, parent, renderer);

			list_append(&ent->branch, ent_list);
		}
		else
			continue;

		obj_json = json_object_get(arr_json, "x");
		if (json_is_number(obj_json))
			entity_set_position_x(ent, json_number_value(obj_json));

		obj_json = json_object_get(arr_json, "y");
		if (json_is_number(obj_json))
			entity_set_position_y(ent, json_number_value(obj_json));

		obj_json = json_object_get(arr_json, "sprite");
		if (json_is_string(obj_json)) {
			if (ent->sprite != NULL)
				sprite_destroy(ent->sprite);
			ent->sprite = sprite_create_file(json_string_value(obj_json),
					textures, renderer);
		}

		obj_json = json_object_get(arr_json, "properties");
		if (json_is_object(obj_json))
			property_list_create_json(&ent->properties, obj_json);
	}

	return 0;
}

struct entity *entity_create_json(json_t *root, struct list *textures,
		struct entity *parent, SDL_Renderer *renderer)
{
	if (!json_is_object(root)) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Can't create entity. JSON is not object."
				);
		return NULL;
	}

	json_t *iter_json = NULL;

	const char *name = NULL;
	struct entity *ent = NULL;
	struct sprite *sprite = NULL;

	iter_json = json_object_get(root, "name");
	if (json_is_string(iter_json))
		name = json_string_value(iter_json);

	iter_json = json_object_get(root, "sprite");
	if (json_is_string(iter_json))
		sprite = sprite_create_file(json_string_value(iter_json),
				textures, renderer);

	ent = entity_create(sprite, name, parent);

	iter_json = json_object_get(root, "children");
	if (json_is_array(iter_json))
		entity_list_create_json(&ent->children,
				iter_json, textures, ent, renderer);

	iter_json = json_object_get(root, "properties");
	if (json_is_object(iter_json))
		property_list_create_json(&ent->properties, iter_json);

	iter_json = json_object_get(root, "collisions");
	if (json_is_array(iter_json))
		collision_object_list_create_json(&ent->col_objs, iter_json,
				&ent->position);

	return ent;
}

struct entity *entity_create_file(const char *filename,
		struct list *textures, struct entity *parent, SDL_Renderer *renderer)
{
	uint8_t *buf = NULL;
	PHYSFS_sint64 read_length = 0;
	json_t *root_node = NULL;
	json_error_t error;
	struct entity *ent = NULL;

	read_length = fs_read_buffer(filename, &buf);
	if (read_length == 0) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Got no data from '%s'",
				filename
				);
		return NULL;
	}

	SDL_Log("Reading object - %s - size: %i", filename, read_length);

	root_node = json_loadb(buf, read_length, 0, &error);
	free(buf);

	if (root_node == NULL) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON error for file '%s' - line: %d - message: %s.",
				filename, error.line, error.text
				);
		return NULL;
	}

	ent = entity_create_json(root_node, textures, parent, renderer);
	json_decref(root_node);
	return ent;
}

struct entity *entity_list_find_first(struct list *entities, const char *name)
{
	struct entity *iter;
	list_for_each_entry(iter, entities, branch)
	{
		if (strcmp(iter->name, name) == 0)
			return iter;
	}

	return NULL;
}

float entity_get_number_property(struct entity *ent, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0)
			return iter->value.n;
	}

	return 0.0f;
}

uint8_t entity_get_bool_property(struct entity *ent, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0)
			return iter->value.b;
	}

	return 0;
}

const char *entity_get_string_property(struct entity *ent, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0)
			return iter->value.s;
	}

	return "";
}

struct sprite *entity_get_sprite(struct entity *entity)
{
	return entity->sprite;
}

const char *entity_get_name(struct entity *entity)
{
	return entity->name;
}

struct entity *entity_get_parent(struct entity *entity)
{
	return entity->parent;
}

float entity_get_position_x(struct entity *entity)
{
	return entity->position.x;
}

float entity_get_position_y(struct entity *entity)
{
	return entity->position.y;
}

struct list *entity_get_collision_objects(struct entity *ent)
{
	return &ent->col_objs;
}

void entity_set_position_x(struct entity *entity, float x)
{
	entity->position.x = x;
}

void entity_set_position_y(struct entity *entity, float y)
{
	entity->position.y = y;
}

void entity_set_number_property(struct entity *ent, float value, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0) {
			iter->type = NUMBER;
			iter->value.n = value;
			return;
		}
	}

	list_append(&property_create_number(value, name)->list,
			&ent->properties);
}

void entity_set_bool_property(struct entity *ent, uint8_t value, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0) {
			iter->type = BOOL;
			iter->value.b = value;
			return;
		}
	}

	list_append(&property_create_bool(value, name)->list,
			&ent->properties);
}

void entity_set_string_property(struct entity *ent, const char *value, const char *name)
{
	struct property *iter;
	list_for_each_entry(iter, &ent->properties, list)
	{
		if (strcmp(iter->name, name) == 0) {
			iter->type = STRING;
			free(iter->value.s);
			iter->value.s = malloc(strlen(value) + 1);
			strcpy(iter->value.s, value);
			return;
		}
	}

	list_append(&property_create_string(value, name)->list,
			&ent->properties);
}
