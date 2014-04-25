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
#include <libxml/parser.h>
#include <libxml/tree.h>
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

void HandleFrame(Frame* frame, xmlNodePtr root)
{
	xmlNodePtr iter = root;

	while (iter != NULL)
	{
		if (iter->type == XML_ATTRIBUTE_NODE)
		{
		}
		else if (iter->type == XML_TEXT_NODE)
		{
			if (xmlStrEqual(iter->parent->name, "x"))
			{
				frame->rect.x = atoi(iter->content);
			}
			else if (xmlStrEqual(iter->parent->name, "y"))
			{
				frame->rect.y = atoi(iter->content);
			}
			else if (xmlStrEqual(iter->parent->name, "width"))
			{
				frame->rect.w = atoi(iter->content);
			}
			else if (xmlStrEqual(iter->parent->name, "height"))
			{
				frame->rect.h = atoi(iter->content);
			}
		}

		HandleFrame(frame, iter->children);

		iter = iter->next;
	}
}

void FillSpriteWithXML(Sprite* sprite, xmlNodePtr root)
{
	xmlNodePtr iter = root;
	
	while (iter != NULL)
	{
		if (iter->type == XML_TEXT_NODE)
		{
			if (xmlStrEqual(iter->parent->name, "img") == 1)
			{
				sprite->texture = GetTexture(iter->content);
			}
		}
		else if (iter->type == XML_ELEMENT_NODE)
		{
			if (xmlStrEqual(iter->name, "frame"))
			{
				Frame** frame = &(sprite->frames);
				while (*frame != NULL)
					frame = &((*frame)->next);
				(*frame) = malloc(sizeof(Frame));
				(*frame)->next = NULL;

				HandleFrame(*frame, iter);
				sprite->numFrames += 1;
			}
			else
			{
				FillSpriteWithXML(sprite, iter->children);
			}
		}

		iter = iter->next;
	}
}

Sprite* LoadSprite(const char* filename)
{
	PHYSFS_File* file = NULL;
	PHYSFS_sint64 fileLength = 0;
	uint8_t* buf = NULL;
	xmlDocPtr doc = NULL;
	xmlNodePtr rootNode = NULL;
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
	buf = malloc(fileLength);
	PHYSFS_read(file, buf, 1, fileLength);
	PHYSFS_close(file);

	doc = xmlReadMemory(buf, fileLength, NULL, "utf-8", 0);
	free(buf);
	buf = NULL;

	if (doc == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not read sprite file '%s'.",
				filename
				);
		return NULL;
	}

	rootNode = xmlDocGetRootElement(doc);

	if (rootNode == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find root node in sprite file '%s'.",
				filename
				);
		return NULL;
	}

	sprite = CreateSprite();

	FillSpriteWithXML(sprite, rootNode);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return sprite;
}
