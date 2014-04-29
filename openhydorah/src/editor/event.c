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

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		DestroyObjectList(editor->selected);
		editor->selected = NULL;
		editor->showSelectionBox = 1;

		editor->selectionStart.x = event->button.x;
		editor->selectionStart.y = event->button.y;
		editor->selectionRect.x = event->button.x;
		editor->selectionRect.y = event->button.y;
		editor->selectionRect.w = 1;
		editor->selectionRect.h = 1;

			/*SDL_Point point;
			point.x = event->button.x;
			point.y = event->button.y;

			AddSelection(&editor->selected,
					FindObjectInPoint(editor->map->objects, point)
					);
			*/
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		editor->selectionRect.h = event->motion.y - editor->selectionRect.y;
		editor->selectionRect.w = event->motion.x - editor->selectionRect.x;
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		editor->showSelectionBox = 0;

		// Convert start position to top-left
		if (editor->selectionRect.w < 0)
		{
			editor->selectionRect.x = event->motion.x;
			editor->selectionRect.w = editor->selectionStart.x - editor->selectionRect.x;
		}

		if (editor->selectionRect.h < 0)
		{
			editor->selectionRect.y = event->motion.y;
			editor->selectionRect.h = editor->selectionStart.y - editor->selectionRect.y;
		}		

		editor->selected = FindObjectsInRect(editor->map->objects,
				editor->selectionRect);
	}
}
