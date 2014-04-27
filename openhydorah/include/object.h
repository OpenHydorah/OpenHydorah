#ifndef OPENHYDORAH_OBJECT_H
#define OPENHYDORAH_OBJECT_H

#include "sprite.h"
#include <SDL.h>

typedef struct SObject {
	Sprite* sprite;
	SDL_Point point;
	struct SObject* children;
	struct SObject* parent;
	struct SObject* next;
} Object;

Object* CreateObject(Sprite* sprite, SDL_Point point, Object* parent);

void DrawObject(Object* object, SDL_Renderer* renderer);

void DestroyObject(Object* object);

void AddChild(Object* parent, Object* child);

#endif // OPENHYDORAH_OBJECT_H
