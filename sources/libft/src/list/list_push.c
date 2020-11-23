#include <stdlib.h>
#include "list.h"
#include "util.h"

void	list_push_back(t_list *list, void *item)
{
	t_list_node	*node;

	node = malloc(sizeof(t_list_node));
	ft_assert(node != NULL, __func__, "malloc error");
	node->data = item;
	node->prev = list->back;
	node->next = NULL;
	if (list->back != NULL)
		list->back->next = node;
	list->back = node;
	if (list->front == NULL)
		list->front = node;
	++list->size;
}

void	list_push_front(t_list *list, void *item)
{
	t_list_node	*node;

	node = malloc(sizeof(t_list_node));
	ft_assert(node != NULL, __func__, "malloc error");
	node->data = item;
	node->prev = NULL;
	node->next = list->front;
	if (list->front != NULL)
		list->front->prev = node;
	list->front = node;
	if (list->back == NULL)
		list->back = node;
	++list->size;
}
