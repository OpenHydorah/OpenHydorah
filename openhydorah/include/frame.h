#ifndef OPENHYDORAH_FRAME_H
#define OPENHYDORAH_FRAME_H

#include <SDL.h>
#include <jansson.h>

typedef struct SFrame {
	char* name;
	SDL_Rect rect;
	struct SFrame* next;
} Frame;

Frame* CreateFrame(void);
Frame* CreateFrameFromJSON(json_t* root);
Frame* CreateFramesFromJSON(json_t* root);
Frame* FindFrameByName(Frame* frames, const char* name);

#endif // OPENHYDORAH_FRAME_H
