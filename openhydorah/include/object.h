#ifndef OPENHYDORAH_OBJECT_H
#define OPENHYDORAH_OBJECT_H

#include "sprite.h"
#include <SDL.h>
#include <jansson.h>

typedef struct SObject {
	Sprite* sprite;
	char* name;
	SDL_Point point;
	struct SObject* children;
	struct SObject* parent;
	struct SObject* next;
} Object;

Object* CreateObject(Sprite* sprite, const char* name,
		SDL_Point point, Object* parent);

Object* CreateObjectFromJSON(json_t* root, SDL_Point point,
		TextureList** textures, Object* parent);

Object* CreateObjectsFromJSON(json_t* root, TextureList** textures,
		Object* parent);

Object* CreateObjectFromFile(const char* filename, SDL_Point point,
		TextureList** textures, Object* parent);

void DrawObject(Object* object, SDL_Renderer* renderer);

void DestroyObject(Object* object);

void AddChildObject(Object* parent, Object* child);

Object* FindObjectInPoint(Object* root, SDL_Point point);

#endif // OPENHYDORAH_OBJECT_H
