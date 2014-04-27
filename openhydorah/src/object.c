#include "object.h"

Object* CreateObject(Sprite* sprite, SDL_Point point, Object* parent)
{
	Object* obj = malloc(sizeof(Object));
	obj->sprite = sprite;
	obj->point = point;
	obj->parent = parent;
	obj->children = NULL;
	obj->next = NULL;
	AddChild(parent, obj);
	
	return obj;
}

void DrawObject(Object* object, SDL_Renderer* renderer)
{
	if (object == NULL) return;

	SDL_Point point;
	if (object->parent != NULL)
	{
		point = object->parent->point;
		point.x += object->point.x;
		point.y += object->point.y;
	}
	else
		point = object->point;

	DrawSpriteAtPoint(object->sprite, point, renderer);
	DrawObject(object->children, renderer);
}

void DestroyObject(Object* object)
{
	while (object != NULL)
	{
		DestroyObject(object->children);
		DestroySprite(object->sprite);
		Object* temp = object;
		object = object->next;
		free(temp);
	}
}

void AddChild(Object* parent, Object* child)
{
	if (parent == NULL || child == NULL)
		return;

	Object** iter = &(parent->children);
	while (*iter != NULL)
		iter = &((*iter)->next);

	*iter = child;
}
