#include "map.h"
#include <physfs.h>
#include <stdint.h>
#include <stdlib.h>

Map* CreateMap(Object* objects)
{
	Map* map = malloc(sizeof(Map));
	if (map == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to allocate memory for map"
				);
		return NULL;
	}
	map->objects = objects;

	return map;
}

Map* CreateMapFromFile(const char* filename, TextureList** textures)
{
	Map* map = NULL;
	uint8_t* buf = NULL;
	PHYSFS_sint64 readLength = 0;
	json_t* rootNode = NULL;
	json_error_t error;

	readLength = ReadFileToBuffer(filename, &buf);
	if (readLength == 0)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Got no data from '%s'",
				filename
				);
		return NULL;
	}

	SDL_Log("Reading map - %s - size: %i", filename, readLength);

	rootNode = json_loadb(buf, readLength, 0, &error);
	free(buf);

	if (rootNode == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"JSON error for file '%s' - line: %d - message: %s.",
				filename, error.line, error.text
				);
		return NULL;
	}

	map = CreateMapFromJSON(rootNode, textures);

	return map;
}

Map* CreateMapFromJSON(json_t* root, TextureList** textures)
{
	Map* map = NULL;
	Object* objects = NULL;

	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Invalid map file format. Root is not object"
				);
		json_decref(root);
		return NULL;
	}

	json_t* objectsJSON = json_object_get(root, "objects");
	if (!json_is_array(objectsJSON))
	{
		SDL_LogWarn(
				SDL_LOG_CATEGORY_APPLICATION,
				"No objects array in map file."
				);
	}
	else {
		objects = CreateObjectsFromJSON(objectsJSON, textures, NULL);
	}

	map = CreateMap(objects);

	json_decref(root);

	return map;
}

void DestroyMap(Map* map)
{
	SDL_Log("Destroying map");
	DestroyObject(map->objects);
	free(map);
}

void DrawMap(Map* map, SDL_Renderer* renderer)
{
	if (map == NULL) return;
	
	Object* iter = map->objects;
	while (iter != NULL)
	{
		DrawObject(iter, renderer);
		iter = iter->next;
	}
}
