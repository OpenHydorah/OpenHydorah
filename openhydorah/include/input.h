/** \file input.h
 * Contains structs and functions for inputs
 */

#ifndef OPENHYDORAH_INPUT_H
#define OPENHYDORAH_INPUT_H

#include <SDL.h>
#include <stdint.h>
#include <jansson.h>
#include "list.h"

/**
 * \enum input_type
 *
 * Defines the type of the input
 */
enum input_type {
	KEY
};

typedef void (*input_callback)(void*, const char*);

/**
 * \struct input
 *
 * A user input is a association of
 * an action and an input
 */
struct input {
	char *action;
	uint16_t value;
	enum input_type type;
	SDL_Scancode code;
	input_callback callback;
	struct list list;
};

/**
 * \struct input_preset
 *
 * An input preset is a collection of
 * inputs associated with a name
 */
struct input_preset {
	char *name;
	struct list inputs;
	struct list list;
};

/**
 * \brief Creates an input as a keyboard key
 *
 * \param[in] action Name of the action
 * \param[in] code The key code
 *
 * \return The new input. NULL if error.
 */
struct input *input_create_key(const char *action, SDL_Scancode code);

/**
 * \brief Creates an input from a json object
 *
 * \param[in] root The json object
 *
 * \return The new input
 */
struct input *input_create_json(const char *action, json_t *root);

/**
 * \param[in] name The name of the preset
 *
 * \return The new input preset. NULL if error.
 */
struct input_preset *input_preset_create(const char *name);

/**
 * \brief Creates input presets from file
 *
 * \param[out] list The list to append to
 * \param[in] filename Path to the file to read
 *
 * \return 0 on success. Non-zero on error
 */
uint8_t input_preset_list_create_file(struct list *list, const char *filename);

/**
 * \brief Creates a input preset from a JSON object
 *
 * \param[in] name Name of the preset
 * \param[in] root The JSON object
 *
 * \return The new input preset
 */
struct input_preset *input_preset_create_json(const char *name, json_t *root);

/**
 * \brief Get the value of the input associated with the action
 *
 * \param[in] preset The input preset to look through
 * \param[in] action The action to look for
 *
 * \return The value or 0 if not found.
 */
uint16_t input_preset_get_action_value(struct input_preset *preset,
		const char *action);

/**
 * \brief Adds a callback to an action
 *
 * \param[in] preset The input preset
 * \param[in] action The input action
 * \param[in] callback The callback
 */
void input_preset_add_callback(struct input_preset *preset, const char *action,
		input_callback callback);

/**
 * \param[in] input The input to destroy
 */
void input_destroy(struct input *input);

/**
 * \param[in] preset The input preset to destroy
 */
void input_preset_destroy(struct input_preset *preset);

/**
 * \brief Get the maximum possible value for any input
 *
 * \return The maximum value
 */
uint16_t input_get_max_value(void);

#endif // OPENHYDORAH_INPUT_H
