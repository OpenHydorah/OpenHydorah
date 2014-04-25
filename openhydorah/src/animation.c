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

#include "animation.h"
#include <SDL.h>
#include <string.h>

Animation* CreateAnimation(void)
{
	Animation* animation = malloc(sizeof(Animation));
	if (animation == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_SYSTEM,
				"Failed to allocate memory for animation\n"
				);
		return NULL;
	}

	animation->name = NULL;
	animation->frames = NULL;
	animation->next = NULL;

	return animation;
}

Animation* CreateAnimationFromJSON(json_t* root, Frame* frames)
{
	if (!json_is_object(root))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Animation is invalid JSON type. Expected object.\n"
		);

		json_decref(root);
		return NULL;
	}

	json_t* name = NULL;
	json_t* frameNodes = NULL;
	Animation* animation = NULL;
	uint32_t i = 0;

	name = json_object_get(root, "name");
	if (!json_is_string(name))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find name for animation.\n"
		);

		json_decref(root);
		return NULL;
	}

	animation = CreateAnimation();
	if (animation == NULL)
		return NULL;

	size_t size = strlen(json_string_value(name));
	animation->name = malloc(size);
	strcpy(animation->name, json_string_value(name));

	frameNodes = json_object_get(root, "frames");
	if (!json_is_array(frameNodes))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not get 'frames' array for animation '%s'.\n",
			animation->name
		);

		json_decref(root);
		return NULL;
	}

	Frame** fIter2 = &animation->frames;
	for (i = 0; i < json_array_size(frameNodes); i++)
	{
		json_t* frame = NULL;
		Frame* fIter = NULL;
		int found = 0;

		frame = json_array_get(frameNodes, i);
		if (!json_is_string(frame))
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid frame value for frames in animation '%s'",
				animation->name
				);
			continue;
		}

		fIter = frames;
		while (fIter != NULL)
		{
			if (strcmp(fIter->name, json_string_value(frame)) == 0)
			{
				found = 1;
				while (*fIter2 != NULL)
					fIter2 = &((*fIter2)->next);

				(*fIter2) = malloc(sizeof(Frame));
				(*fIter2)->rect = fIter->rect;
				size_t size = strlen(fIter->name);
				(*fIter2)->name = malloc(sizeof(size));
				strcpy((*fIter2)->name, fIter->name);
				(*fIter2)->next = NULL;
				break;
			}

			fIter = fIter->next;
		}

		if (found == 0)
		{
			SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"No frame found for JSON animation frame '%s'",
					json_string_value(frame)
					);
		}
	}
}
