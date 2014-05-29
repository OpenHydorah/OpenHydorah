#include "animation.h"

#include <stdlib.h>
#include <string.h>
#include <SDL.h>

struct animation *animation_create(const char *name, struct frame **frames,
		uint32_t num_frames)
{
	struct animation *animation = malloc(sizeof(*animation));
	if (animation == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate memory for animation."
				);
		return NULL;
	}

	animation->name = malloc(strlen(name) + 1);
	strcpy(animation->name, name);

	animation->frames = frames;
	animation->num_frames = num_frames;

	return animation;
}

struct animation *animation_create_json(json_t *root, struct frame **frames,
		uint32_t num_frames)
{
	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON for animation is not an object."
				);
		return NULL;
	}

	json_t *iter_json;
	const char *name;
	struct frame **sel_frames; // frames that the animation will use
	uint32_t num_sel_frames;
	uint32_t i;

	iter_json = json_object_get(root, "name");
	if (!json_is_string(iter_json))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"'name' entry of animation has no string value."
				);
		return NULL;
	}
	name = json_string_value(iter_json);

	iter_json = json_object_get(root, "frames");
	if (!json_is_array(iter_json))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"'frames' entry of animation has no array value."
				);
		return NULL;
	}

	num_sel_frames = json_array_size(iter_json);
	sel_frames = calloc(num_sel_frames, sizeof(*sel_frames));
	for (i = 0; i < num_sel_frames; i++)
	{
		json_t *name_json;
		name_json = json_array_get(iter_json, i);

		sel_frames[i] = frame_array_find(frames, num_frames,
				json_string_value(name_json));
	}

	return animation_create(name, sel_frames, num_sel_frames);
}

struct animation **animation_array_create_json(json_t *root, struct frame **frames,
		uint32_t num_frames, uint32_t *num)
{
	if (!json_is_array(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON for animation array is not an array."
				);
		return NULL;
	}

	*num = json_array_size(root);
	if (*num == 0)
		return NULL;

	struct animation **animations = calloc(*num, sizeof(**animations));
	uint32_t i;

	for (i = 0; i < *num; i++)
	{
		json_t *anim_node;

		anim_node = json_array_get(root, i);
		if (!json_is_object(anim_node))
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Animation is invalid JSON type. Expected object.\n"
			);
			continue;
		}

		animations[i] = animation_create_json(anim_node, frames, num_frames);
	}

	return animations;
}

void animation_destroy(struct animation *animation)
{
	free(animation->frames);
	free(animation->name);
	free(animation);
}
