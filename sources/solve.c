#include <stdlib.h>
#include "str.h"
#include "lem.h"
#include "mem.h"
#include "util.h"
#include "list.h"
#include "lem_solve.h"

#define NOT_VISITED (-1)

static int		bfs_internal(t_graph *g, int *layer)
{
	t_list		*queue;
	int			v;
	t_list_node	*link;
	t_link		*e;

	queue = list_new();
	list_push_back(queue, (void *)(long long)g->start);
	layer[g->start] = 0;
	while (queue->size > 0 && layer[g->end] == NOT_VISITED)
	{
		v = (int)(long long)list_pop_front(queue);
		link = ((t_room *)g->rooms->storage[v])->links->front;
		while (link != NULL)
		{
			e = (t_link *)g->links->storage[(size_t)link->data];
			if (layer[e->to] == NOT_VISITED && e->flow < e->cap)
			{
				list_push_back(queue, (void *)(long long)e->to);
				layer[e->to] = layer[v] + 1;
			}
			link = link->next;
		}
	}
	list_clear(&queue, NULL);
	return (layer[g->end] != NOT_VISITED);
}

static int		bfs(t_graph *g, int *layer)
{
	size_t	i;

	if (!bfs_internal(g, layer))
		return (0);
	i = 0;
	while (i < g->rooms->size)
	{
		g->last[i] = ((t_room *)g->rooms->storage[i])->links->front;
		++i;
	}
	return (1);
}

static int		dfs(t_graph *g, int *layer, int v, int flow)
{
	t_link	*e;
	t_link	*e_rev;
	int		pushed;

	if (flow == 0)
		return (0);
	if (v == g->end)
		return (flow);
	while (g->last[v] != NULL)
	{
		e = (t_link *)g->links->storage[(size_t)g->last[v]->data];
		e_rev = (t_link *)g->links->storage[(size_t)g->last[v]->data ^ 1UL];
		if (layer[e->to] == layer[v] + 1)
		{
			pushed = dfs(g, layer, e->to, flow < e->cap - e->flow ? flow : e->cap - e->flow);
			if (pushed != 0)
			{
				e->flow += pushed;
				e_rev->flow -= pushed;
				return (pushed);
			}
		}
		g->last[v] = g->last[v]->next;
	}
	return (0);
}

static void		choose_best_paths(t_list **best_paths, t_list *cur_paths,
									 double *best_turns, double cur_turns)
{
	if (*best_paths == NULL || cur_turns < *best_turns)
	{
		if (*best_paths != NULL)
		{
			list_clear(best_paths, NULL);//free func
			//free(*best_paths);
		}
		*best_paths = cur_paths;
		*best_turns = cur_turns;
	}
	else
	{
		list_clear(&cur_paths, NULL);//free func
		//free(cur_paths);
	}
}

t_list			*dinic(t_graph *g)
{
	t_list	*best_paths;
	t_list	*cur_paths;
	double	best_turns;
	double	cur_turns;
	int		*layer;

	best_paths = NULL;
	best_turns = 0.0;
	g->last = malloc(g->rooms->size * sizeof(t_list_node *));
	layer = malloc(g->rooms->size * sizeof(int ));
	ft_assert(layer != NULL, __func__, "malloc error");
	while (1)
	{
		ft_memset(layer, NOT_VISITED, g->rooms->size * sizeof(int));
		if (!bfs(g, layer))
			break ;
		while (dfs(g, layer, g->start, INT_MAX))
		{
			cur_paths = get_paths(g);
			cur_turns = count_turns(cur_paths, g->ants);
			choose_best_paths(&best_paths, cur_paths, &best_turns, cur_turns);
		}
	}
	return (best_paths);
}
