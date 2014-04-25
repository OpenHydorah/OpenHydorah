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

#ifndef OPENHYDORAH_DICTIONARY_H
#define OPENHYDORAH_DICTIONARY_H

typedef struct SDictionary {
	char* name;
	void* data;
	struct SDictionary* next;
} Dictionary;

void AddToDictionary(Dictionary** dict, const char* name, void* data);

void* GetFromDict(Dictionary* dict, const char* name);

#endif // OPENHYDORAH_DICTIONARY_H
