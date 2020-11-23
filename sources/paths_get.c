#include <stdlib.h>
#include "io.h"
#include "str.h"
#include "lem.h"
#include "mem.h"
#include "util.h"
#include "list.h"

static void		get_vertex(t_graph *g, int v, t_list *cur_path)
{
	t_list_node	*node;
	t_link	*edge;

	if (cur_path->size == 0 ||
		(size_t)cur_path->back->data != ((size_t)v ^ 1UL))
	{
		list_push_back(cur_path, (void *)(long long)v);
	}
	if (v == g->end)
	{
		return ;
	}
	node = ((t_room *)g->rooms->storage[v])->links->front;
	while (node != NULL)
	{
		edge = (t_link *)g->links->storage[(size_t)node->data];
		if (edge->flow > 0)
		{
			get_vertex(g, edge->to, cur_path);
		}
		node = node->next;
	}
}

t_list			*get_paths(t_graph *g)
{
	t_list	*paths;
	t_list	*cur_path;
	t_list_node	*node;
	t_link	*edge;

//	paths = (t_list *)malloc(sizeof(t_list));
//	if (paths == NULL)
//		ft_throw(ALLOC_MSG, E_ALLOC);
	paths = list_new();
	node = ((t_room *)g->rooms->storage[g->start])->links->front;
	while (node != NULL)
	{
		edge = (t_link *)g->links->storage[(size_t)node->data];
		if (edge->flow > 0)
		{
			//cur_path = (t_list *)malloc(sizeof(t_list));
			//if (cur_path == NULL)
			//	ft_throw(ALLOC_MSG, E_ALLOC);
			cur_path = list_new();
			get_vertex(g, edge->to, cur_path);
			list_push_back(paths, cur_path);
		}
		node = node->next;
	}
	return (paths);
}

double			count_turns(t_list *paths, int number_of_ants)
{
	t_list_node	*node;
	t_list	*path;
	double	avg_path_len;
	double	avg_ants_per_path;

	avg_path_len = 0.0;
	node = paths->front;
	while (node != NULL)
	{
		path = (t_list *)node->data;
		avg_path_len += path->size;
		node = node->next;
	}
	avg_path_len /= paths->size;
	avg_ants_per_path = (double)number_of_ants / paths->size;
	return (avg_ants_per_path - 1 + avg_path_len);
}

