#include "input.h"

#include <string.h>
#include <jansson.h>
#include "filesystem.h"
#include <stdlib.h>
#include <stdio.h>

uint16_t input_get_max_value(void)
{
	return 0x7FFF;
}

struct input *input_create_key(const char *action, SDL_Scancode code)
{
	struct input *input = malloc(sizeof(*input));
	uint32_t len = strlen(action);
	input->action = malloc(len + 1);
	strcpy(input->action, action);
	input->value = 0;

	input->type = KEY;
	input->code = code;
	input->callback = NULL;

	return input;
}

struct input *input_create_json(const char *action, json_t *root)
{
	if (!json_is_object(root))
		return NULL;

	json_t *iter;
	const char *type;

	iter = json_object_get(root, "type");
	if (!json_is_string(iter))
		return NULL;

	type = json_string_value(iter);

	if (strcmp(type, "key") == 0)
	{
		iter = json_object_get(root, "key");
		if (!json_is_string(iter))
			return NULL;

		return input_create_key(action,
				SDL_GetScancodeFromName(json_string_value(iter)));
	}
}

struct input_preset *input_preset_create(const char *name)
{
	struct input_preset *preset = malloc(sizeof(*preset));
	if (preset == NULL)
		return NULL;

	preset->name = malloc(strlen(name) + 1);
	strcpy(preset->name, name);

	list_init(&preset->inputs);
	list_init(&preset->list);

	return preset;
}

uint8_t input_preset_list_create_file(struct list *list, const char *filename)
{
	struct input_preset *preset = NULL;
	uint8_t* buf = NULL;
	PHYSFS_sint64 read_len = 0;
	json_t* root = NULL;
	json_error_t json_error;
	const char* preset_key;
	json_t* preset_value = NULL;

	read_len = fs_read_buffer(filename, &buf);

	if (read_len == 0)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to read keymap from file: '%s'\n",
				filename
				);
		return 1;
	}

	root = json_loadb(buf, read_len, 0, &json_error);
	free(buf);

	if (root == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to read keymap file as JSON: '%s'\n",
				json_error.text
				);
		return 1;
	}

	json_object_foreach(root, preset_key, preset_value)
	{
		preset = input_preset_create_json(preset_key, preset_value);
		if (preset != NULL)
			list_append(&preset->list, list);
	}

	json_decref(root);
	return 0;
}

struct input_preset *input_preset_create_json(const char *name, json_t *root)
{
	if (!json_is_object(root))
		return NULL;

	const char *key;
	json_t *value;
	struct input *input = NULL;
	struct input_preset *preset = NULL;

	preset = input_preset_create(name);

	json_object_foreach(root, key, value)
	{
		input = input_create_json(key, value);
		if (input != NULL)
			list_append(&input->list, &preset->inputs);
	}

	return preset;
}

uint16_t input_preset_get_action_value(struct input_preset *preset,
		const char *action)
{
	if (preset == NULL)
		return 0;

	const uint8_t* state = SDL_GetKeyboardState(NULL);
	struct input *iter;
	list_for_each_entry(iter, &preset->inputs, list)
	{
		if (strcmp(iter->action, action) == 0)
		{
			if (iter->type == KEY && state[iter->code])
			{
				return input_get_max_value();
			}
		}
	}

	return 0;
}

void input_preset_add_callback(struct input_preset *preset, const char *action,
		input_callback callback)
{
	if (preset == NULL && callback == NULL)
		return;

	struct input *iter;
	list_for_each_entry(iter, &preset->inputs, list)
	{
		if (strcmp(iter->action, action) == 0)
			iter->callback = callback;
	}
}

void input_destroy(struct input *input)
{
	free(input->action);
	free(input);
}

void input_preset_destroy(struct input_preset *preset)
{
	struct input *iter, *next;
	list_for_each_entry_safe(iter, next, &preset->inputs, list)
	{
		input_destroy(iter);
	}

	free(preset->name);
	free(preset);
}
