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

#ifndef OPENHYDORAH_ANIMATION_H
#define OPENHYDORAH_ANIMATION_H

#include "frame.h"
#include <jansson.h>

typedef struct SAnimation {
	char* name;
	Frame* frames;
	Frame* start;
	struct SAnimation* next;
} Animation;

Animation* CreateAnimation(void);

Animation* CreateAnimationFromJSON(json_t* root, Frame* frames);

#endif // OPENHYDORAH_ANIMATION_H
