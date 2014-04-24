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

typedef struct SFrame {
	SDL_Rect rect;
	struct SFrame* next;
} Frame;

typedef struct {
	char* img;
	Frame* frames;
	uint32_t numFrames;
} Sprite;

Sprite* LoadSprite(const char* filename);

#endif // OPENHYDORAH_SPRITE_H
