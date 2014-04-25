/*
This file is part of OpenHydorah.

OpenHydorah is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenHydorah is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenHydorah.  If not, see <http://www.gnu.org/licenses/>.
*/

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
			break;

		frames = frames->next;
	}

	return frames;
}
