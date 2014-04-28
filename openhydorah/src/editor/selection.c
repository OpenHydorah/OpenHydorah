#include "editor.h"

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
