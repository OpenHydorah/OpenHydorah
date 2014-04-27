#include "object.h"

#include "filesystem.h"
#include <string.h>

Object* CreateObject(Sprite* sprite, const char* name, SDL_Point point, Object* parent)
{
	Object* obj = malloc(sizeof(Object));
	obj->sprite = sprite;
	if (name != NULL)
	{
		size_t len = strlen(name);
		obj->name = malloc(len);
		strcpy(obj->name, name);
	}
	else
		obj->name = NULL;
	obj->point = point;
	obj->parent = parent;
	obj->children = NULL;
	obj->next = NULL;
	AddChildObject(parent, obj);
	
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
		free(temp->name);
		free(temp);
	}
}

void AddChildObject(Object* parent, Object* child)
{
	if (parent == NULL || child == NULL)
		return;

	Object** iter = &(parent->children);
	while (*iter != NULL)
		iter = &((*iter)->next);

	*iter = child;
}

Object* CreateObjectsFromJSON(json_t* root, TextureList** textures)
{
	if (!json_is_array(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Can't create objects. JSON is not array."
				);
		json_decref(root);
		return NULL;
	}

	uint32_t i = 0;
	Object* objects = NULL;
	Object** objIter = &objects;
	for (i = 0; i < json_array_size(root); i++)
	{
		json_t* elem = NULL;
		json_t* objJSON = NULL;
		json_t* xJSON = NULL;
		json_t* yJSON = NULL;
		SDL_Point point;

		elem = json_array_get(root, i);
		if (!json_is_object(elem))
		{
			SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"Element in objects array is not JSON object."
					);
			continue;
		}

		xJSON = json_object_get(elem, "x");
		if (json_is_integer(xJSON))
		{
			point.x = json_integer_value(xJSON);
		}

		yJSON = json_object_get(elem, "y");
		if (json_is_integer(yJSON))
		{
			point.y = json_integer_value(yJSON);
		}

		objJSON = json_object_get(elem, "object");
		if (json_is_string(objJSON))
		{
			(*objIter) = CreateObjectFromFile(json_string_value(objJSON), point, textures);
			objIter = &((*objIter)->next);
		}
		else if(json_is_object(objJSON))
		{
			(*objIter) = CreateObjectFromJSON(objJSON, point, textures);
			objIter = &((*objIter)->next);
		}
		else
		{
			SDL_LogWarn(
					SDL_LOG_CATEGORY_APPLICATION,
					"Unknown object element, for array element, for objects in JSON."
					);
		}
	}

	return objects;
}

Object* CreateObjectFromJSON(json_t* root, SDL_Point point, TextureList** textures)
{
	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Can't create object. JSON is not object."
				);
		json_decref(root);
		return NULL;
	}

	json_t* nameJSON = NULL;
	json_t* childrenJSON = NULL;
	json_t* spriteJSON = NULL;

	char* name = NULL;
	Object* children = NULL;
	Object* obj = NULL;
	Sprite* sprite = NULL;

	nameJSON = json_object_get(root, "name");
	if (json_is_string(nameJSON))
	{
		strcpy(name, json_string_value(nameJSON));
	}

	childrenJSON = json_object_get(root, "children");
	if (json_is_array(childrenJSON))
	{
		children = CreateObjectsFromJSON(childrenJSON, textures);
	}

	spriteJSON = json_object_get(root, "sprite");
	if (json_is_string(spriteJSON))
	{
		sprite = GetSprite(json_string_value(spriteJSON), textures);
	}

	obj = CreateObject(sprite, name, point, NULL);

	return obj;
}

Object* CreateObjectFromFile(const char* filename, SDL_Point point, TextureList** textures)
{
	Object* obj = NULL;
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

	SDL_Log("Reading object - %s - size: %i", filename, readLength);

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

	obj = CreateObjectFromJSON(rootNode, point, textures);

	return obj;
}
