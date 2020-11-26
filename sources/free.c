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

void	free_coords(t_hashmap **coords)
{
	void	*ptr;
	size_t	i;
	t_list	*room_coords;

	i = 0;
	while (hashmap_iter(*coords, &i, NULL, &ptr))
	{
		room_coords = (t_list *)ptr;
		list_clear(&room_coords, NULL);
	}
	hashmap_destroy(coords);
}

void	free_graph(t_graph **g)
{
	hashmap_destroy(&(*g)->rooms_names);
	free_coords(&(*g)->coords);
	free_array_list(&(*g)->links, free);
	free_array_list(&(*g)->rooms, free_room);
	free(*g);
	*g = NULL;
}