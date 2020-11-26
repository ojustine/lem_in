#include "str.h"
#include "lem_structs.h"
#include "list.h"
#include "util.h"

static void		get_path(t_graph *g, int v, t_list *path)
{
	register t_list_node	*node;
	t_link					*edge;

	if (path->size == 0 || (size_t)path->back->data != ((size_t)v ^ 1UL))
		list_push_back(path, (void *)(long long)v);
	if (v == g->end)
		return ;
	node = ((t_room *)arrlist_peek(g->rooms, v))->links->front;
	while (node != NULL)
	{
		edge = (t_link *)arrlist_peek(g->links, (size_t)node->data);
		if (edge->flow > 0)
			get_path(g, edge->to, path);
		node = node->next;
	}
}

t_list			*get_paths(t_graph *g)
{
	t_list					*paths;
	t_list					*cur_path;
	t_link					*edge;
	register t_list_node	*node;

	paths = list_new();
	ft_assert(paths != NULL, __func__, "malloc error");
	node = ((t_room *)arrlist_peek(g->rooms, g->start))->links->front;
	while (node != NULL)
	{
		edge = (t_link *)arrlist_peek(g->links, (size_t)node->data);
		if (edge->flow > 0)
		{
			cur_path = list_new();
			ft_assert(cur_path != NULL, __func__, "malloc error");
			get_path(g, edge->to, cur_path);
			list_push_back(paths, cur_path);
		}
		node = node->next;
	}
	return (paths);
}

double			paths_avg_turns(t_list *paths, int number_of_ants)
{
	t_list_node	*node;
	t_list		*path;
	double		avg_path_len;
	double		avg_ants_per_path;

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

