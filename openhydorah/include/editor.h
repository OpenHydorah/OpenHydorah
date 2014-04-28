#ifndef OPENHYDORAH_EDITOR_H
#define OPENHYDORAH_EDITOR_H

#include <SDL.h>
#include "object.h"
#include "map.h"

typedef struct SSelection {
	Object* object;
	struct SSelection* next;
} Selection;

typedef struct {
	int active;
	Map* map;
	Selection* selected;
} Editor;

Editor* CreateEditor(Map* map);

void ShowEditor(Editor* editor);

void HideEditor(Editor* editor);

void RenderEditor(Editor* editor, SDL_Renderer* renderer);

void DestroyEditor(Editor* editor);

void AddSelection(Selection** selection, Object* object);

void DestroySelection(Selection* selection);

void HandleEditorEvents(Editor* editor, SDL_Event* event);

#endif // OPENHYDORAH_EDITOR_H
