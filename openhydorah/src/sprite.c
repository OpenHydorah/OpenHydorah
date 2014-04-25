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

#include "sprite.h"
#include <physfs.h>
#include <SDL.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

Sprite* CreateSprite(void)
{
	Sprite* sprite = malloc(sizeof(Sprite));
	if (sprite == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_SYSTEM,
				"Failed to allocate data for sprite"
				);
		return NULL;
	}

	sprite->texture = NULL;
	sprite->frames = NULL;
	sprite->numFrames = 0;
	sprite->animations = NULL;
	sprite->numAnimations = 0;
	sprite->currentFrame = NULL;

	return sprite;
}

Sprite* CreateSpriteFromJSON(json_t* root, TextureList** textures)
{
	json_t* frames = NULL;
	json_t* currentFrame = NULL;
	json_t* animations = NULL;
	json_t* img = NULL;
	uint32_t i = 0;
	Sprite* sprite = NULL;

	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid sprite file format\n"
				);
		return NULL;
	}

	sprite = CreateSprite();
	
	img = json_object_get(root, "img");
	if (!json_is_string(img))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'img' value\n"
			);
		json_decref(root);
		return NULL;
	}
	sprite->texture = GetTextureFromList(*textures, json_string_value(img));
	if (sprite->texture == NULL)
	{
		sprite->texture = GetTexture(json_string_value(img));
		AddTextureToList(textures, json_string_value(img), sprite->texture);
	}

	frames = json_object_get(root, "frames");
	if (!json_is_array(frames))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'frames' array\n"
			);
		json_decref(root);
		return NULL;
	}

	for (i = 0; i < json_array_size(frames); i++)
	{
		json_t* frameNode;

		frameNode = json_array_get(frames, i);
		if (!json_is_object(frameNode))
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Frame is invalid JSON type. Expected object.\n"
			);
			continue;
		}

		Frame** frame = &(sprite->frames);
		while (*frame != NULL)
			frame = &((*frame)->next);

		*frame = CreateFrameFromJSON(frameNode);
		if(*frame == NULL)
		{
			continue;
		}
		sprite->numFrames += 1;
	}

	animations = json_object_get(root, "animations");
	if (!json_is_array(animations))
	{
		SDL_LogWarn(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'animations' array\n"
			);
	}
	else
	{
		for (i = 0; i < json_array_size(animations); i++)
		{
			json_t* animNode;

			animNode = json_array_get(animations, i);
			if (!json_is_object(animNode))
			{
				SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"Animation is invalid JSON type. Expected object.\n"
				);
				continue;
			}

			Animation** anims = &(sprite->animations);
			Frame* frames = (sprite->frames);
			while (*anims != NULL)
				anims = &((*anims)->next);

			*anims = CreateAnimationFromJSON(animNode, frames);
			if(*anims == NULL)
			{
				continue;
			}
			sprite->numAnimations += 1;
		}
	}

	currentFrame = json_object_get(root, "default_frame");
	if (!json_is_string(currentFrame))
	{
		SDL_LogWarn(
			SDL_LOG_CATEGORY_APPLICATION,
			"No default_frame for sprite\n"
			);

		sprite->currentFrame = sprite->frames;
	}
	else
	{
		sprite->currentFrame = FindFrameByName(sprite->frames,
				json_string_value(currentFrame));
		if (sprite->currentFrame == NULL)
		{
			SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find frame '%s' for default_frame, for sprite\n",
				json_string_value(currentFrame)
				);

			sprite->currentFrame = sprite->frames;
		}
	}

	return sprite;
}

RefPtr GetSprite(const char* filename, TextureList** textures)
{
	RefPtr refPtr = NULL;
	PHYSFS_File* file = NULL;
	PHYSFS_sint64 fileLength = 0;
	uint8_t* buf = NULL;
	json_t* rootNode = NULL;
	json_error_t error;
	Sprite* sprite = NULL;

	if (PHYSFS_exists(filename) == 0)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find file '%s'.",
				filename
				);
		return NULL;
	}

	file = PHYSFS_openRead(filename);
	if (file == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not open file '%s'.",
				filename
				);
		return NULL;
	}

	fileLength = PHYSFS_fileLength(file);
	SDL_Log("Reading sprite - %s - size: %i", filename, fileLength);
	buf = malloc(fileLength);
	PHYSFS_read(file, buf, 1, fileLength);
	PHYSFS_close(file);

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
	
	if (sprite == NULL)
	{
		return NULL;
	}

	json_decref(rootNode);

	refPtr = CreateRefPtr(sprite, DestroySprite);

	return refPtr;
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

void DestroySprite(void* sprite)
{
	SDL_Log("Destroying sprite");
	Sprite* spr = sprite;

	DestroyFrames(spr->frames);
	free(spr);
}

void DrawSprite(RefPtr spriteRef, SDL_Renderer* renderer)
{
	if (spriteRef == NULL || spriteRef->ptr == NULL)
		return;
	Sprite* sprite = spriteRef->ptr;

	if (sprite == NULL || sprite->texture == NULL ||
			sprite->frames == NULL)
		return;
	Texture* tex = sprite->texture;

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = sprite->currentFrame->rect.w;
	rect.h = sprite->currentFrame->rect.h;
	SDL_RenderCopy(renderer, tex, &(sprite->currentFrame->rect), &rect);

	sprite->currentFrame = sprite->currentFrame->next;
	if (sprite->currentFrame == NULL)
		sprite->currentFrame = sprite->frames;
}
