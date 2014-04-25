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

	return sprite;
}

Sprite* CreateSpriteFromJSON(json_t* root, Dictionary** textures)
{
	json_t* frames = NULL;
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
	sprite->texture = GetFromDict(*textures, json_string_value(img));
	if (sprite->texture == NULL)
	{
		sprite->texture = GetTexture(json_string_value(img));
		AddToDictionary(textures, json_string_value(img), sprite->texture);
	}

	frames = json_object_get(root, "frames");
	if (!json_is_array(frames))
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Could not find 'img' value\n"
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
		if(frame == NULL)
		{
			continue;
		}
		sprite->numFrames += 1;
	}

	return sprite;
}

RefPtr GetSprite(const char* filename, Dictionary** textures)
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

	DestroyRefPtr(&(spr->texture));
	DestroyFrames(spr->frames);
	free(spr);
}

void DrawSprite(RefPtr spriteRef, SDL_Renderer* renderer)
{
	if (spriteRef == NULL || spriteRef->ptr == NULL)
		return;
	Sprite* sprite = spriteRef->ptr;

	if (sprite == NULL || sprite->texture == NULL ||
			sprite->texture->ptr == NULL || sprite->frames == NULL)
		return;
	Texture* tex = sprite->texture->ptr;

	SDL_RenderCopy(renderer, tex, &(sprite->frames->rect), NULL);
}
