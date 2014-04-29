#include "editor.h"

#include <stdlib.h>

Editor* CreateEditor(Map* map)
{
	SDL_Log("Creating editor");
	Editor* editor = malloc(sizeof(Editor));
	editor->active = 0;
	editor->selected = NULL;
	editor->map = map;
	editor->gridWidth = 32;
	editor->gridHeight = 32;
	editor->showGrid = 0;
	editor->showCollisions = 0;
	editor->showSelectionBox = 0;
	editor->isDragging = 0;

	return editor;
}

void ShowEditor(Editor* editor)
{
	SDL_Log("Show editor");
	editor->active = 1;
}

void HideEditor(Editor* editor)
{
	SDL_Log("Hide editor");
	editor->active = 0;
}

void DestroyEditor(Editor* editor)
{
	SDL_Log("Destroying editor");
	free(editor);
}

