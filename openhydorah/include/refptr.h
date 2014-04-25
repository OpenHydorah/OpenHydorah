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

#ifndef OPENHYDORAH_REFPTR_H
#define OPENHYDORAH_REFPTR_H

#include <stdint.h>

typedef struct SRefPtr {
	void* ptr;
	void (*DestroyFunc)(void*);
	uint32_t refCount;
	struct SRefPtr* refSource;
} *RefPtr;

RefPtr CreateRefPtr(void* ptr, void(*DestroyFunc)(void*));

RefPtr CopyRefPtr(RefPtr ptr);

void DestroyRefPtr(RefPtr* ptr);

#endif // OPENHYDORAH_REFPTR_H
