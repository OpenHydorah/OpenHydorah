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

#ifndef OPENHYDORAH_SPRITE_H
#define OPENHYDORAH_SPRITE_H

#include <SDL.h>
#include <stdint.h>
#include "texture.h"
#include "refptr.h"
#include "dictionary.h"
#include "frame.h"
#include "animation.h"
#include <jansson.h>

typedef struct {
	RefPtr texture;
	Frame* frames;
	Animation* animations;
	uint32_t numFrames;
	uint32_t numAnimations;
	Frame* currentFrame;
} Sprite;

Sprite* CreateSprite(void);

Sprite* CreateSpriteFromJSON(json_t* root, Dictionary** textures);

RefPtr GetSprite(const char* filename, Dictionary** textures);

void DestroySprite(void* sprite);

void DrawSprite(RefPtr spriteRef, SDL_Renderer* renderer);

#endif // OPENHYDORAH_SPRITE_H
