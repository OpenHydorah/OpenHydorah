#include "editor.h"
#include <stdlib.h>

void DrawEditor(Editor* editor, SDL_Renderer* renderer)
{
	if (editor == NULL || !editor->active) return;

	if (editor->showGrid)
		RenderEditorGrid(editor, renderer);
	if (editor->showCollisions)
		DrawObjectCollisions(editor->map->objects, renderer);
	RenderSelection(editor->selected, renderer);
	if (editor->showSelectionBox)
		RenderSelectionBox(editor, renderer);
}

void RenderSelection(ObjectList* selection, SDL_Renderer* renderer)
{
	while (selection != NULL)
	{
		if (selection->object == NULL)
		{
			selection = selection->next;
			continue;
		}

		Object* obj = selection->object;
		if (obj->sprite == NULL || obj->sprite->currentFrame == NULL)
		{
			selection = selection->next;
			continue;
		}

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

void RenderEditorGrid (Editor* editor, SDL_Renderer* renderer)
{
	uint32_t width, height;
	uint32_t numX, numY;
	uint32_t i;

	if (SDL_GetRendererOutputSize(renderer, &width, &height) != 0)
		return;

	numX = abs(width / editor->gridWidth);
	numY = abs(height / editor->gridHeight);

	SDL_SetRenderDrawColor(renderer, 50,50,50,255);

	for (i = 1; i <= numX; i++)
	{
		SDL_RenderDrawLine(renderer,
				editor->gridWidth * i, 0,
				editor->gridWidth * i, height
				);
	}

	for (i = 1; i <= numY; i++)
	{
		SDL_RenderDrawLine(renderer,
				0, editor->gridHeight * i,
				width, editor->gridHeight * i
				);
	}

	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

void RenderSelectionBox(Editor* editor, SDL_Renderer* renderer)
{
	if (editor == NULL) return;

	SDL_SetRenderDrawColor(renderer, 0,255,0,255);

	SDL_RenderDrawRect(renderer, &editor->selectionRect);

	SDL_SetRenderDrawColor(renderer, 0,255,0,120);

	SDL_RenderFillRect(renderer, &editor->selectionRect);
	
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}
