#ifndef OPENHYDORAH_EDITOR_H
#define OPENHYDORAH_EDITOR_H

#include <SDL.h>
#include "object.h"
#include "map.h"
#include <stdint.h>

typedef struct {
	uint8_t active;
	Map* map;
	ObjectList* selected;
	SDL_Rect selectionRect;
	SDL_Point selectionStart;
	uint32_t gridWidth;
	uint32_t gridHeight;
	uint8_t showCollisions;
	uint8_t showGrid;
	uint8_t showSelectionBox;
} Editor;

Editor* CreateEditor(Map* map);

void ShowEditor(Editor* editor);

void HideEditor(Editor* editor);

void DrawEditor(Editor* editor, SDL_Renderer* renderer);

void DestroyEditor(Editor* editor);

void RenderSelection(ObjectList* selection, SDL_Renderer* renderer);

void RenderSelectionObjects(Object* obj, SDL_Renderer* renderer);

void HandleEditorEvents(Editor* editor, SDL_Event* event);

void RenderEditorGrid (Editor* editor, SDL_Renderer* renderer);

void RenderSelectionBox(Editor* editor, SDL_Renderer* renderer);

#endif // OPENHYDORAH_EDITOR_H
