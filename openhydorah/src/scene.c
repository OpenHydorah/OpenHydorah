#include "scene.h"
#include <physfs.h>
#include <stdint.h>
#include <stdlib.h>

struct scene *scene_create(void)
{
	struct scene *scene = malloc(sizeof(*scene));
	if (scene == NULL) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate memory for scene"
				);
		return NULL;
	}

	list_init(&scene->entities);
	list_init(&scene->sprites);

	return scene;
}

struct scene *scene_create_file(const char *filename, struct list *textures,
		SDL_Renderer *renderer)
{
	uint8_t *buf = NULL;
	PHYSFS_sint64 read_length = 0;
	json_t *root_node = NULL;
	json_error_t error;
	struct scene *scene = NULL;

	read_length = fs_read_buffer(filename, &buf);
	if (read_length == 0) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Got no data from '%s'",
				filename
				);
		return NULL;
	}

	SDL_Log("Reading scene - %s - size: %i", filename, read_length);

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

	scene = scene_create_json(root_node, textures, renderer);
	json_decref(root_node);
	return scene;
}

struct scene *scene_create_json(json_t *root, struct list *textures,
		SDL_Renderer *renderer)
{
	if (!json_is_object(root)) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid scene file format. Root is not object"
				);
		return NULL;
	}

	struct scene *scene = scene_create();

	json_t *ent_json = json_object_get(root, "entities");
	if (!json_is_array(ent_json)) {
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"No objects array in scene file."
				);
	} else {
		entity_list_create_json(&scene->entities,
				ent_json, textures, NULL, renderer);
	}

	return scene;
}

void scene_destroy(struct scene *scene)
{
	if (scene == NULL)
		return;

	SDL_Log("Destroying scene");

	struct entity *iter;
	struct entity *next;
	list_for_each_entry_safe(iter, next, &scene->entities, branch)
	{
		entity_destroy(iter);
	}

	free(scene);
}

void scene_draw(struct scene *scene, SDL_Renderer *renderer)
{
	if (scene == NULL)
		return;

	struct entity *iter;
	list_for_each_entry(iter, &scene->entities, branch)
	{
		entity_draw(iter, renderer);
	}
}

struct list *scene_get_entities(struct scene *scene)
{
	return &scene->entities;
}
