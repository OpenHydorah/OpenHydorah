#ifndef OPENHYDORAH_EDITOR_H
#define OPENHYDORAH_EDITOR_H

#include <SDL.h>
#include "object.h"

typedef struct SSelection {
	Object* object;
	struct SSelection* next;
} Selection;

typedef struct {
	int active;
	Selection* selected;
} Editor;

Editor* CreateEditor(void);

void ShowEditor(Editor* editor);

void HideEditor(Editor* editor);

void RenderEditor(Editor* editor, SDL_Renderer* renderer);

void DestroyEditor(Editor* editor);

void AddSelection(Selection** selection, Object* object);

void DestroySelection(Selection* selection);

#endif // OPENHYDORAH_EDITOR_H
