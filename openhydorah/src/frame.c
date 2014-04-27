#include "frame.h"

Frame* CreateFrame(void)
{
	Frame* frame = malloc(sizeof(Frame));

	if (frame == NULL)
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_SYSTEM,
			"Failed to allocate memory for frame\n"
			);
		return NULL;
	}
	
	frame->name = NULL;
	frame->next = NULL;

	return frame;
}

Frame* CreateFrameFromJSON(json_t* root)
{
	if (!json_is_object(root))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Frame is invalid JSON type. Expected object.\n"
		);

		return NULL;
	}

	json_t* name = NULL;
	json_t *x,*y,*width,*height;
	Frame* frame = NULL;

	name = json_object_get(root, "name");
	if (!json_is_string(name))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find name for frame.\n"
		);

		return NULL;
	}

	frame = CreateFrame();
	if (frame == NULL)
		return NULL;

	size_t size = strlen(json_string_value(name));
	frame->name = malloc(size);
	strcpy(frame->name, json_string_value(name));

	x = json_object_get(root, "x");
	if (!json_is_integer(x))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not get x value for frame '%s'",
				frame->name
				);
	}
	else
		frame->rect.x = json_integer_value(x);

	y = json_object_get(root, "y");
	if (!json_is_integer(y))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not get y value for frame '%s'",
				frame->name
				);
	}
	else
		frame->rect.y = json_integer_value(y);

	width = json_object_get(root, "width");
	if (!json_is_integer(width))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not get width value for frame '%s'",
				frame->name
				);
	}
	else
		frame->rect.w = json_integer_value(width);

	height = json_object_get(root, "height");
	if (!json_is_integer(height))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not get height value for frame '%s'",
				frame->name
				);
	}
	else
		frame->rect.h = json_integer_value(height);

	return frame;
}

Frame* FindFrameByName(Frame* frames, const char* name)
{
	while (frames != NULL)
	{
		if (strcmp(frames->name, name) == 0)
			return frames;

		frames = frames->next;
	}

	return frames;
}
