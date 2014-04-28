#include "editor.h"

void HandleEditorEvents(Editor* editor, SDL_Event* event)
{
	if (editor == NULL) return;

	if (event->type == SDL_KEYDOWN)
	{
		SDL_Scancode scancode = event->key.keysym.scancode;
		if (scancode == SDL_SCANCODE_E)
		{
			if (editor->active)
				HideEditor(editor);
			else
				ShowEditor(editor);
		}

		if (!editor->active)
			return;

		if (scancode == SDL_SCANCODE_C)
			editor->showCollisions = (editor->showCollisions ? 0 : 1);
	}

	if (!editor->active)
		return;

	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (editor->map != NULL)
		{
			DestroySelection(editor->selected);
			editor->selected = NULL;

			SDL_Point point;
			point.x = event->button.x;
			point.y = event->button.y;

			AddSelection(&editor->selected,
					FindObjectInPoint(editor->map->objects, point)
					);
		}
	}
}
