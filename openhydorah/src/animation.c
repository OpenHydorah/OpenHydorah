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
	animation->start = NULL;

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
	json_t* start = NULL;
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
	animation->name = malloc(size + 1);
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

	Frame** fIter = &animation->frames;
	for (i = 0; i < json_array_size(frameNodes); i++)
	{
		json_t* frame = NULL;
		Frame* foundFrame = NULL;

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

		foundFrame = FindFrameByName(frames, json_string_value(frame));
		if (foundFrame != NULL)
		{
			while (*fIter != NULL)
				fIter = &((*fIter)->next);

			(*fIter) = malloc(sizeof(Frame));
			(*fIter)->rect = foundFrame->rect;
			size_t size = strlen(foundFrame->name);
			(*fIter)->name = malloc(size + 1);
			strcpy((*fIter)->name, foundFrame->name);
			(*fIter)->next = NULL;
		}
		else
		{
			SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"No frame found for JSON animation frame '%s'",
					json_string_value(frame)
					);
		}
	}

	start = json_object_get(root, "start");
	if (!json_is_string(start))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"start not found for animation"
			);

		animation->start = animation->frames;
	}
	else
	{
		animation->start = FindFrameByName(animation->frames,
				json_string_value(start));
		if (animation->start == NULL)
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find frame for start, for animation"
			);

			animation->start = animation->frames;
		}
	}

	return animation;
}

Animation* CreateAnimationsFromJSON(json_t* root, Frame* frames)
{
	Animation* animations = NULL;
	Animation** anims = &animations;
	uint32_t i = 0;

	for (i = 0; i < json_array_size(root); i++)
	{
		json_t* animNode;

		animNode = json_array_get(root, i);
		if (!json_is_object(animNode))
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Animation contains invalid JSON type. Expected object.\n"
			);
			continue;
		}

		while (*anims != NULL)
			anims = &((*anims)->next);

		*anims = CreateAnimationFromJSON(animNode, frames);
	}

	return animations;
}
