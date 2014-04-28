#include "collision.h"

CollisionBox CreateCollisionBoxFromJSON(json_t* root)
{
	CollisionBox box;
	json_t* xJSON;
	json_t* yJSON;
	json_t* widthJSON;
	json_t* heightJSON;

	if (!json_is_object(root))
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"CollisionBox is not JSON object."
				);
		return box;
	}

	xJSON = json_object_get(root, "x");
	if (json_is_integer(xJSON))
	{
		box.x = json_integer_value(xJSON);
	}

	yJSON = json_object_get(root, "y");
	if (json_is_integer(yJSON))
	{
		box.y = json_integer_value(yJSON);
	}

	widthJSON = json_object_get(root, "width");
	if (json_is_integer(widthJSON))
	{
		box.w = json_integer_value(widthJSON);
	}

	heightJSON = json_object_get(root, "height");
	if (json_is_integer(heightJSON))
	{
		box.h = json_integer_value(heightJSON);
	}

	return box;
}
