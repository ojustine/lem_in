#include <stdlib.h>
#include "str.h"
#include "lem_structs.h"
#include "mem.h"
#include "math.h"
#include "util.h"
#include "list.h"
#include "lem_solve.h"
#include "lem_paths.h"
#include "lem_free.h"

#define NOT_VISITED (-1)

static int		bfs(t_graph *g, int *layer)
{
	t_link		*edge;
	t_list		*queue;
	t_list_node	*link;
	int			v;

	ft_assert((queue = list_new()) != NULL, __func__, "malloc error");
	list_push_back(queue, &g->start);
	layer[g->start] = 0;
	while (queue->size > 0 && layer[g->end] == NOT_VISITED)
	{
		v = *(int *)list_pop_front(queue);
		link = ((t_room *)arrlist_peek(g->rooms, v))->links->front;
		while (link != NULL)
		{
			edge = (t_link *)arrlist_peek(g->links, (size_t)link->data);
			if (layer[edge->to] == NOT_VISITED && edge->flow < edge->cap)
			{
				list_push_back(queue, &edge->to);
				layer[edge->to] = layer[v] + 1;
			}
			link = link->next;
		}
	}
	list_clear(&queue, NULL);
	return (layer[g->end] != NOT_VISITED);
}

static int		dfs(t_graph *g, int *layer, int v, int flow)
{
	t_link	*dir;
	t_link	*rev;
	int		pushed;

	if (flow == 0)
		return (0);
	if (v == g->end)
		return (flow);
	while (g->last[v] != NULL)
	{
		dir = (t_link *)arrlist_peek(g->links, (size_t)g->last[v]->data);
		rev = (t_link *)arrlist_peek(g->links, (size_t)g->last[v]->data ^ 1UL);
		if (layer[dir->to] == layer[v] + 1)
		{
			pushed = dfs(g, layer, dir->to, ft_min(flow, dir->cap - dir->flow));
			if (pushed != 0)
			{
				dir->flow += pushed;
				rev->flow -= pushed;
				return (pushed);
			}
		}
		g->last[v] = g->last[v]->next;
	}
	return (0);
}

static void		restore_links(t_graph *g)
{
	register size_t	i;

	i = 0;
	while (i < g->rooms->size)
	{
		g->last[i] = ((t_room *)arrlist_peek(g->rooms, i))->links->front;
		++i;
	}
}

static void		choose_best_paths(t_list **best_paths, t_list *cur_paths,
				int	ants_num)
{
	static double	best_turns;
	double			cur_turns;

	cur_turns = paths_avg_turns(cur_paths, ants_num);
	if (*best_paths == NULL || cur_turns < best_turns)
	{
		if (*best_paths != NULL)
			list_clear(best_paths, free_path);
		*best_paths = cur_paths;
		best_turns = cur_turns;
	}
	else
		list_clear(&cur_paths, free_path);
}

t_list			*solve(t_graph *g)
{
	t_list	*best_paths;
	t_list	*cur_paths;
	int		*layer;

	best_paths = NULL;
	g->last = malloc(g->rooms->size * sizeof(t_list_node *));
	layer = malloc(g->rooms->size * sizeof(int ));
	ft_assert(layer != NULL && g->last != NULL, __func__, "malloc error");
	while (1)
	{
		ft_memset(layer, NOT_VISITED, g->rooms->size * sizeof(int));
		if (!bfs(g, layer))
			break ;
		restore_links(g);
		while (dfs(g, layer, g->start, INT_MAX))
		{
			cur_paths = get_paths(g);
			choose_best_paths(&best_paths, cur_paths, g->ants);
		}
	}
	free(g->last);
	free(layer);
	return (best_paths);
}
