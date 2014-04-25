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

#include "refptr.h"

#include <stdlib.h>

RefPtr CreateRefPtr(void* ptr, void(*DestroyFunc)(void*))
{
	RefPtr refPtr = malloc(sizeof(struct SRefPtr));
	refPtr->ptr = ptr;
	refPtr->DestroyFunc = DestroyFunc;
	refPtr->refCount = 0;
	refPtr->refSource = refPtr;

	return refPtr;
}

RefPtr CopyRefPtr(RefPtr ptr)
{
	RefPtr refPtr = malloc(sizeof(struct SRefPtr));
	refPtr->ptr = ptr->ptr;
	refPtr->DestroyFunc = NULL;
	refPtr->refCount = 0;
	ptr->refSource->refCount += 1;
	refPtr->refSource = ptr->refSource;

	return refPtr;
}

void DestroyRefPtr(RefPtr* ptr)
{
	if ((*ptr)->refSource != NULL)
	{
		if ((*ptr)->refSource->refCount == 0)
		{
			(*ptr)->refSource->DestroyFunc((*ptr)->refSource->ptr);
		}
		else {
			(*ptr)->refSource->refCount -= 1;
		}
	}

	free(*ptr);
	*ptr = NULL;
}
