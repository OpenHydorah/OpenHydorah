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

#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

void AddToDictionary(Dictionary** dict, const char* name, void* data)
{
	Dictionary** iter = dict;

	while (*iter != NULL)
		iter = &((*iter)->next);

	(*iter) = malloc(sizeof(Dictionary));
	(*iter)->name = malloc(strlen(name));
	strcpy((*iter)->name, name);
	(*iter)->data = data;
}

void* GetFromDict(Dictionary* dict, const char* name)
{
	Dictionary* iter = dict;
	while (iter != NULL)
	{
		if (strcmp(iter->name, name) == 0)
		{
			return iter->data;
		}

		iter = iter->next;
	}

	return NULL;
}
