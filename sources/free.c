#include <stdlib.h>
#include "lem_structs.h"
#include "list.h"

void	free_path(void *data)
{
	t_list	*path;

	path = (t_list *)data;
	list_clear(&path, NULL);
}

void	free_room(void *data)
{
	t_room	*room;

	room = (t_room *)data;
	list_clear(&room->links, NULL);
	free(room->name);
	free(room);
}

void	free_array_list(t_arrlist **vector, void (*f)(void *))
{
	size_t	i;

	i = 0;
	while (i < (*vector)->size)
	{
		f((*vector)->storage[i]);
		++i;
	}
	free((*vector)->storage);
	free(*vector);
}

void	free_graph(t_graph **g)
{
	hashmap_destroy(&(*g)->rooms_names);
	hashmap_destroy(&(*g)->coords);
	free_array_list(&(*g)->links, free);
	free_array_list(&(*g)->rooms, free_room);
	free(*g);
	*g = NULL;
}