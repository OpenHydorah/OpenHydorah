#include "property.h"

#include <string.h>
#include <stdlib.h>

struct property *property_create_number(float value, const char *name)
{
	struct property *property = malloc(sizeof(*property));
	if (property == NULL)
		return NULL;

	property->name = malloc(strlen(name) + 1);
	strcpy(property->name, name);

	property->type = NUMBER;
	property->value.n = value;

	list_init(&property->list);

	return property;
}

struct property *property_create_string(const char *value, const char *name)
{
	struct property *property = malloc(sizeof(*property));
	if (property == NULL)
		return NULL;

	property->name = malloc(strlen(name) + 1);
	strcpy(property->name, name);

	property->type = STRING;
	property->value.s = malloc(strlen(value) + 1);
	strcpy(property->value.s, value);

	return property;
}

struct property *property_create_bool(uint8_t value, const char *name)
{
	struct property *property = malloc(sizeof(*property));
	if (property == NULL)
		return NULL;

	property->name = malloc(strlen(name) + 1);
	strcpy(property->name, name);

	property->type = BOOL;
	property->value.b = value;

	return property;
}

void property_destroy(struct property *property)
{
	free(property->name);
	if (property->type == STRING)
		free(property->value.s);
	free(property);
}

uint8_t property_list_create_json(struct list *list, json_t *root)
{
	if (!json_is_object(root))
		return 1;

	const char *key;
	json_t *value;
	struct property *iter;
	struct property *list_iter;
	uint8_t found;

	json_object_foreach(root, key, value) {
		iter = NULL;
		found = 0;
		if (json_is_number(value))
			iter = property_create_number(json_number_value(value), key);
		else if (json_is_boolean(value)) {
			if (json_is_true(value))
				iter = property_create_bool(1, key);
			else if (json_is_false(value))
				iter = property_create_bool(0, key);
		}
		else if (json_is_string(value))
			iter = property_create_string(json_string_value(value), key);

		if (iter != NULL) {
			list_for_each_entry(list_iter, list, list)
			{
				if (strcmp(list_iter->name, key) == 0) {
					if (list_iter->type == STRING)
						free(list_iter->value.s);
					list_iter->type = iter->type;
					list_iter->value = iter->value;
					found = 1;
				}
			}
			if (!found)
				list_append(&iter->list, list);
		}
	}

	return 0;
}
