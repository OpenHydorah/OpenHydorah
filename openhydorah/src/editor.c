#include "editor.h"

#include <stdlib.h>

Editor* CreateEditor(void)
{
	SDL_Log("Creating editor");
	Editor* editor = malloc(sizeof(Editor));
	editor->active = 0;
	editor->selected = NULL;

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

void RenderSelectionObjects(Object* obj, SDL_Renderer* renderer)
{
	while (obj != NULL)
	{
		if (obj->sprite == NULL || obj->sprite->currentFrame == NULL)
			continue;

		SDL_Rect rect;
		rect.x = obj->point.x;
		rect.y = obj->point.y;
		rect.w = obj->sprite->currentFrame->rect.w;
		rect.h = obj->sprite->currentFrame->rect.h;

		SDL_RenderDrawRect(renderer, &rect);
		if (obj->parent != NULL)
		{
			SDL_RenderDrawLine(renderer,
					obj->parent->point.x + obj->parent->sprite->currentFrame->rect.w / 2,
					obj->parent->point.y + obj->parent->sprite->currentFrame->rect.h / 2,
					rect.x + rect.w / 2,
					rect.y + rect.h / 2);
		}

		RenderSelectionObjects(obj->children, renderer);

		obj = obj->next;
	}
}

void RenderSelection(Selection* selection, SDL_Renderer* renderer)
{
	while (selection != NULL)
	{
		if (selection->object == NULL)
			continue;

		Object* obj = selection->object;
		if (obj->sprite == NULL || obj->sprite->currentFrame == NULL)
			continue;

		SDL_Rect rect;
		rect.x = selection->object->point.x;
		rect.y = selection->object->point.y;
		rect.w = selection->object->sprite->currentFrame->rect.w;
		rect.h = selection->object->sprite->currentFrame->rect.h;

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);
		RenderSelectionObjects(obj->children, renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		selection = selection->next;
	}
}

void RenderEditor(Editor* editor, SDL_Renderer* renderer)
{
	if (editor == NULL || !editor->active) return;

	RenderSelection(editor->selected, renderer);
}

void DestroyEditor(Editor* editor)
{
	SDL_Log("Destroying editor");
	free(editor);
}

void AddSelection(Selection** selection, Object* object)
{
	while(*selection != NULL)
		selection = &((*selection)->next);

	*selection = malloc(sizeof(Selection));
	(*selection)->object = object;
	(*selection)->next = NULL;
}

void DestroySelection(Selection* selection)
{
	while (selection != NULL)
	{
		Selection* temp = selection;
		selection = selection->next;
		free (temp);
	}
}
