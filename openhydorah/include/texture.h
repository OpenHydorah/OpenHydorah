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

#ifndef OPENHYDORAH_TEXTURE_H
#define OPENHYDORAH_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include "refptr.h"

typedef SDL_Texture Texture;

typedef struct STextureList {
	Texture* texture;
	char* name;
	struct STextureList* next;
} TextureList;

TextureList* CreateTextureList(void);

void AddTextureToList(TextureList** list, const char* name, Texture* texture);

Texture* GetTextureFromList(TextureList* list, const char* name);

Texture* GetTexture(const char* filename);

void DestroyTexture(Texture* texture);

void DestroyTextureList(TextureList* list);

#endif // OPENHYDORAH_TEXTURE_H
