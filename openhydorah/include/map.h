#ifndef OPENHYDORAH_MAP_H
#define OPENHYDORAH_MAP_H

#include "object.h"
#include "texture.h"

typedef struct {
	Object* objects;
} Map;

Map* CreateMap(Object* objects);

Map* CreateMapFromJSON(json_t* root, TextureList** textures);

Map* CreateMapFromFile(const char* filename, TextureList** textures);

void DestroyMap(Map* map);

void DrawMap(Map* map, SDL_Renderer* renderer);

#endif // OPENHYDORAH_MAP_H
