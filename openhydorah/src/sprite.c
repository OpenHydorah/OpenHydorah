#include "sprite.h"
#include <physfs.h>
#include <SDL.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct sprite *sprite_create(struct texture *texture, struct frame **frames,
		uint32_t num_frames, struct animation **animations,
		uint32_t num_animations)
{
	struct sprite *sprite = malloc(sizeof(*sprite));
	if (sprite == NULL) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate data for sprite"
				);
		return NULL;
	}

	sprite->texture = texture;
	sprite->frames = frames;
	sprite->animations = animations;
	sprite->num_frames = num_frames;
	sprite->num_animations = num_animations;

	return sprite;
}

struct sprite *sprite_create_json(json_t *root, struct list *textures,
		SDL_Renderer *renderer)
{
	uint32_t i = 0;
	struct texture *texture = NULL;
	struct frame **frames;
	struct animation **animations;
	uint32_t num_frames;
	uint32_t num_animations;
	json_t *iter_json;

	if (!json_is_object(root)) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid sprite file format\n"
				);
		return NULL;
	}

	iter_json = json_object_get(root, "img");
	if (!json_is_string(iter_json)) {
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'img' value\n"
			);
		return NULL;
	}

	texture = texture_list_find(textures, json_string_value(iter_json));
	if (texture == NULL) {
		texture = texture_create_file(json_string_value(iter_json), renderer);
		list_append(&texture->list, textures);
	}

	iter_json = json_object_get(root, "frames");
	if (!json_is_array(iter_json)) {
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'frames' array\n"
			);
		return NULL;
	}

	frames = frame_array_create_json(iter_json, &num_frames);

	iter_json = json_object_get(root, "animations");
	if (json_is_array(iter_json))
		animations = animation_array_create_json(iter_json,
				frames, num_frames, &num_animations);

	json_decref(root);
	return sprite_create(texture_copy(texture),
			frames, num_frames, animations, num_animations);
}

struct sprite *sprite_create_file(const char *filename, struct list *textures,
		SDL_Renderer *renderer)
{
	PHYSFS_sint64 file_length = 0;
	uint8_t *buf = NULL;
	json_t *root_node = NULL;
	json_error_t error;

	file_length = fs_read_buffer(filename, &buf);
	if (file_length == 0) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to read sprite from file: '%s'\n",
				filename
				);
		return NULL;
	}

	SDL_Log("Reading sprite - %s - size: %i", filename, file_length);

	root_node = json_loadb(buf, file_length, 0, &error);
	free(buf);
	buf = NULL;

	if (root_node == NULL) {
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON error for file '%s' - line: %d - message: %s.",
				filename, error.line, error.text
				);
		return NULL;
	}

	return sprite_create_json(root_node, textures, renderer);
}

void sprite_destroy(struct sprite *sprite)
{
	if (sprite == NULL)
		return;

	SDL_Log("Destroying sprite");
	uint32_t i;
	for (i = 0; i < sprite->num_animations; i++)
		animation_destroy(sprite->animations[i]);

	free(sprite->animations);

	for (i = 0; i < sprite->num_frames; i++)
		frame_destroy(sprite->frames[i]);

	free(sprite->frames);

	texture_destroy(sprite->texture);
	free(sprite);
}

void sprite_list_destroy(struct list *sprites)
{
	if (sprites == NULL)
		return;

	struct sprite *iter;
	struct sprite *next;
	list_for_each_entry_safe(iter, next, sprites, list)
	{
		sprite_destroy(iter);
	}
}

void sprite_draw_point(struct sprite *sprite, SDL_Point point,
		SDL_Renderer *renderer)
{
	if (sprite == NULL)
		return;

	SDL_Rect rect;
	rect.x = point.x;
	rect.y = point.y;
	rect.w = sprite->frames[0]->rect.w;
	rect.h = sprite->frames[0]->rect.h;

	if (sprite->texture == NULL) {
		SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		return;
	}

	SDL_Texture *tex = sprite->texture->ptr;
	SDL_RenderCopy(renderer, tex, &(sprite->frames[0]->rect), &rect);
}
