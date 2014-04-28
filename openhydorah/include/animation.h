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

Animation* CreateAnimationsFromJSON(json_t* root, Frame* frames);

#endif // OPENHYDORAH_ANIMATION_H
