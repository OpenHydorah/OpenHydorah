#include "sprite.h"
#include <physfs.h>
#include <SDL.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

Sprite* CreateSprite(Texture* texture, Frame* frames, Frame* defaultFrame, Animation* animations)
{
	Sprite* sprite = malloc(sizeof(Sprite));
	if (sprite == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate data for sprite"
				);
		return NULL;
	}

	sprite->texture = texture;
	sprite->frames = frames;
	sprite->animations = animations;
	if (defaultFrame == NULL)
		sprite->currentFrame = sprite->frames;
	else
		sprite->currentFrame = defaultFrame;
	sprite->activeAnimation = NULL;

	return sprite;
}

Sprite* CreateSpriteFromJSON(json_t* root, TextureList** textures)
{
	json_t* framesJSON = NULL;
	json_t* defaultFrameJSON = NULL;
	json_t* animationsJSON = NULL;
	json_t* imgJSON = NULL;

	uint32_t i = 0;
	Sprite* sprite = NULL;
	Texture* texture = NULL;
	Frame* frames = NULL;
	Frame* defaultFrame = NULL;
	Animation* animations = NULL;

	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid sprite file format\n"
				);
		return NULL;
	}

	imgJSON = json_object_get(root, "img");
	if (!json_is_string(imgJSON))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'img' value\n"
			);
		json_decref(root);
		return NULL;
	}

	texture = GetTextureFromList(*textures, json_string_value(imgJSON));
	if (texture == NULL)
	{
		texture = CreateTextureFromFile(json_string_value(imgJSON));
		AddTextureToList(textures, json_string_value(imgJSON), texture);
	}

	framesJSON = json_object_get(root, "frames");
	if (!json_is_array(framesJSON))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'frames' array\n"
			);
		json_decref(root);
		return NULL;
	}

	frames = CreateFramesFromJSON(framesJSON);

	animationsJSON = json_object_get(root, "animations");
	if (json_is_array(animationsJSON))
	{
		animations = CreateAnimationsFromJSON(animationsJSON, frames);
	}

	defaultFrameJSON = json_object_get(root, "default_frame");
	if (json_is_string(defaultFrameJSON))
	{
		defaultFrame = FindFrameByName(frames,
				json_string_value(defaultFrameJSON));
		if (defaultFrame == NULL)
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find frame '%s' for default_frame, for sprite\n",
				json_string_value(defaultFrameJSON)
				);
		}
	}

	sprite = CreateSprite(texture, frames, defaultFrame, animations);

	return sprite;
}

Sprite* CreateSpriteFromFile(const char* filename, TextureList** textures)
{
	PHYSFS_sint64 fileLength = 0;
	uint8_t* buf = NULL;
	json_t* rootNode = NULL;
	json_error_t error;
	Sprite* sprite = NULL;

	fileLength = ReadFileToBuffer(filename, &buf);
	SDL_Log("Reading sprite - %s - size: %i", filename, fileLength);

	rootNode = json_loadb(buf,fileLength,0,&error);
	free(buf);
	buf = NULL;

	if (rootNode == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON error for file '%s' - line: %d - message: %s.",
				filename, error.line, error.text
				);
		return NULL;
	}

	sprite = CreateSpriteFromJSON(rootNode, textures);
	
	json_decref(rootNode);

	return sprite;
}

void DestroyFrames(Frame* frames)
{
	while (frames != NULL)
	{
		Frame* tempIter = frames;
		frames = frames->next;
		free(tempIter->name);
		free(tempIter);
	}
}

void DestroySprite(Sprite* sprite)
{
	if (sprite == NULL) return;

	SDL_Log("Destroying sprite");

	DestroyFrames(sprite->frames);
	free(sprite);
}

void DrawSpriteAtPoint(Sprite* sprite, SDL_Point point, SDL_Renderer* renderer)
{
	if (sprite == NULL || sprite->currentFrame == NULL)
		return;

	SDL_Rect rect;
	rect.x = point.x;
	rect.y = point.y;
	rect.w = sprite->currentFrame->rect.w;
	rect.h = sprite->currentFrame->rect.h;

	if (sprite->texture == NULL)
	{
		SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		return;
	}

	Texture* tex = sprite->texture;
	SDL_RenderCopy(renderer, tex, &(sprite->currentFrame->rect), &rect);

	if (sprite->activeAnimation != NULL)
	{
		sprite->currentFrame = sprite->currentFrame->next;
		if (sprite->currentFrame == NULL)
			sprite->currentFrame = sprite->activeAnimation->frames;
	}
}
