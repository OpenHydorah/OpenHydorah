#include "engine.h"
#include "init.h"

struct engine *engine_create(void)
{
	struct engine *engine = malloc(sizeof(*engine));
	if (engine == NULL)
		return NULL;

	engine->running = 1;
	engine->current_scene = NULL;
	engine->current_input_preset = NULL;
	engine->current_mod = NULL;
	engine->renderer = NULL;
	engine->window = NULL;

	list_init(&engine->textures);
	list_init(&engine->input_presets);

	return engine;
}

uint8_t engine_init(struct engine *engine, const char *argv[])
{
	if (init_sdl(&engine->window, &engine->renderer, 600, 480) != 0)
		return 1;

	SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_ADD);

	if (init_fs(argv[0]) != 0)
		return 1;
}

void engine_events(struct engine *engine)
{
	if (engine == NULL)
		return;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			engine->running = 0;
		else if (event.type == SDL_KEYDOWN) {
			if (engine->current_input_preset == NULL)
				continue;

			struct input *iter;
			list_for_each_entry(iter,
					&engine->current_input_preset->inputs,
					list)
			{
				if (iter->callback != NULL &&
						iter->type == KEY &&
						iter->code == event.key.keysym.scancode
				   )
					iter->callback(engine, "down");
			}
		} else if (event.type == SDL_KEYUP) {
			if (engine->current_input_preset == NULL)
				continue;

			struct input *iter;
			list_for_each_entry(iter,
					&engine->current_input_preset->inputs,
					list)
			{
				if (iter->callback != NULL &&
						iter->type == KEY &&
						iter->code == event.key.keysym.scancode
					)
					iter->callback(engine, "up");
			}
		}
	}
}

void engine_destroy(struct engine *engine)
{
	if (engine == NULL)
		return;

	if (engine->current_mod != NULL &&
			engine->current_mod->destroy != NULL)
		engine->current_mod->destroy(engine);

	struct input_preset *preset_iter, *preset_next;
	list_for_each_entry_safe(preset_iter, preset_next,
			&engine->input_presets, list)
	{
		input_preset_destroy(preset_iter);
	}

	scene_destroy(engine->current_scene);
	texture_list_destroy(&engine->textures);
	mod_destroy(engine->current_mod);

	if (PHYSFS_isInit() != 0)
		PHYSFS_deinit();
	if (engine->renderer != NULL)
		SDL_DestroyRenderer(engine->renderer);
	if (engine->window != NULL)
		SDL_DestroyWindow(engine->window);
	SDL_Quit();

	free(engine);
}

void engine_draw(struct engine *engine)
{
	scene_draw(engine->current_scene, engine->renderer);
}

void engine_update(struct engine *engine, uint32_t dt)
{
	if (engine == NULL)
		return;

	if (engine->current_mod != NULL &&
			engine->current_mod->update != NULL)
		engine->current_mod->update(engine, dt);
}

uint8_t engine_run(struct engine *engine)
{
	uint32_t last_time = SDL_GetTicks(), current_time, dt;
	while (engine->running) {
		engine_events(engine);

		current_time = SDL_GetTicks();
		dt = (current_time - last_time);
		last_time = current_time;

		engine_update(engine, dt);

		SDL_RenderClear(engine->renderer);

		engine_draw(engine);

		SDL_RenderPresent(engine->renderer);
	}
}

uint8_t engine_load_scene(struct engine *engine, const char *filename)
{
	engine->current_scene = scene_create_file(filename,
			&engine->textures, engine->renderer);

	if (engine->current_scene == NULL)
		return 1;

	return 0;
}

uint8_t engine_load_input_preset(struct engine *engine, const char *filename)
{
	if (input_preset_list_create_file(&engine->input_presets,
				filename) == 0)
		engine->current_input_preset =
			list_entry(engine->input_presets.next,
					typeof(*(engine->current_input_preset)),
					list);
	else
		return 1;

	if (engine->current_input_preset == NULL)
		return 1;

	return 0;
}

uint8_t engine_load_mod(struct engine *engine, const char *filename)
{
	struct mod_info *info = mod_info_get(filename);
	engine->current_mod = mod_create(info);
	if (engine->current_mod != NULL &&
			engine->current_mod->init != NULL)
		engine->current_mod->init(engine);
	else
		return 1;

	if (engine->current_mod == NULL)
		return 1;

	return 0;
}

struct scene *engine_get_current_scene(struct engine *engine)
{
	return engine->current_scene;
}

struct input_preset *engine_get_current_input_preset(struct engine *engine)
{
	return engine->current_input_preset;
}
