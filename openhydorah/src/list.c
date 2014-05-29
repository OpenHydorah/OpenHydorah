#include "list.h"

void list_init(struct list *list)
{
	list->next = list;
	list->prev = list;
}

void list_append(struct list *new, struct list *head)
{
	struct list *iter = head;

	while (iter->next != head)
	{
		iter = iter->next;
	}

	iter->next = new;
	new->next = head;
	new->prev = iter;
}

void list_remove(struct list *list)
{
	list->prev->next = list->next;
	list->next->prev = list->prev;
}
