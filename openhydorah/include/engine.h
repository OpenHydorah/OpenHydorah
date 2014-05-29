/**
 * \file engine.h
 */

#ifndef OPENHYDORAH_ENGINE_H
#define OPENHYDORAH_ENGINE_H

#include "scene.h"
#include "mod.h"
#include "list.h"
#include "input.h"

/**
 * \struct engine
 *
 * The engine struct contains all
 * the data of the OpenHydorah engine
 */
struct engine {
	uint8_t running;

	SDL_Renderer *renderer;
	SDL_Window *window;

	struct scene *current_scene;
	struct mod *current_mod;
	struct input_preset *current_input_preset;
	struct list input_presets;
	struct list textures;
};

struct engine *engine_create(void);

uint8_t engine_init(struct engine *engine, const char *argv[]);

void engine_destroy(struct engine *engine);

void engine_events(struct engine *engine);

void engine_update(struct engine *engine, uint32_t dt);

void engine_draw(struct engine *engine);

uint8_t engine_run(struct engine *engine);

uint8_t engine_load_scene(struct engine *engine, const char *filename);

uint8_t engine_load_input_preset(struct engine *engine, const char *filename);

uint8_t engine_load_mod(struct engine *engine, const char *filename);

/* GETTERS */
struct scene *engine_get_current_scene(struct engine *engine);
struct input_preset *engine_get_current_input_preset(struct engine *engine);

#endif
