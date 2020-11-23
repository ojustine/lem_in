#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "str.h"
#include "lem.h"
#include "mem.h"
#include "util.h"
#include "list.h"
#include "lem_solve.h"

static void		place_ants_on_paths_internal(t_list *paths, int *ants_on_path,
												int *cur_path, t_list_node **node)
{
	if (*cur_path > 0 &&
		((t_list *)(*node)->data)->size + ants_on_path[*cur_path] >=
		((t_list *)(*node)->prev->data)->size + ants_on_path[*cur_path - 1])
	{
		*cur_path = 0;
		*node = paths->front;
	}
}

static void		place_ants_on_paths(t_list *paths, int number_of_ants, int *ants_on_path, t_list_node **ant_pos, int *ant_wait)
{
	int		cur_ant;
	int		cur_path;
	t_list_node	*node;

	cur_ant = 0;
	cur_path = 0;
	node = paths->front;
	while (cur_ant < number_of_ants)
	{
		while (node != NULL && node->next != NULL)
		{
			if (((t_list *)node->data)->size + ants_on_path[cur_path] <=
				((t_list *)node->next->data)->size + ants_on_path[cur_path + 1])
				break ;
			++cur_path;
			node = node->next;
		}
		place_ants_on_paths_internal(paths, ants_on_path, &cur_path, &node);
		ant_pos[cur_ant] = ((t_list *)node->data)->front;
		ant_wait[cur_ant] = ants_on_path[cur_path]++;
		++cur_ant;
	}
}

static void		move_ants_internal(t_graph *g, t_list_node **ant_pos,
								int *ant_wait, int cur_ant, int *printed)
{
	int		room_index;

	if (ant_wait[cur_ant] != 0)
		--ant_wait[cur_ant];
	else if (ant_pos[cur_ant] != NULL)
	{
		if (*printed == 1)
		{
			printf(" ");
		}
		*printed = 1;
		room_index =
				(int)(long long)((t_list_node *)ant_pos[cur_ant])->data;
		printf("L%d-%s", cur_ant + 1, ((t_room *)g->rooms->storage[room_index])->name);
		ant_pos[cur_ant] = ant_pos[cur_ant]->next;
	}
}

static void		move_ants(t_graph *g, t_list_node **ant_pos,
							 int *ant_wait)
{
	int		cur_ant;
	int		printed;

	while (1)
	{
		printed = 0;
		cur_ant = 0;
		while (cur_ant < g->ants)
		{
			move_ants_internal(g, ant_pos, ant_wait, cur_ant, &printed);
			++cur_ant;
		}
		if (!printed)
		{
			break ;
		}
		printf("\n");
	}
}

void	sort_paths(t_list *paths)
{
	t_list_node	*node;
	t_list_node	*check;
	void	*tmp;

	node = paths->front;
	while (node != NULL)
	{
		check = node->next;
		while (check != NULL)
		{
			if (((t_list *)node->data)->size > ((t_list *)check->data)->size)
			{
				tmp = node->data;
				node->data = check->data;
				check->data = tmp;
			}
			check = check->next;
		}
		node = node->next;
	}
}

void			print_paths(t_list *paths, t_graph *g)
{
	int *ants_on_path = ft_memalloc(paths->size * sizeof(int));
	t_list_node **ant_pos = ft_memalloc(g->ants * sizeof(t_list_node *));
	int *ant_wait = ft_memalloc(g->ants * sizeof(int));
	//if (pp.ants_on_path == NULL || pp.ant_pos == NULL || pp.ant_wait == NULL)
	//assert
	sort_paths(paths);
	place_ants_on_paths(paths, g->ants, ants_on_path, ant_pos, ant_wait);
	move_ants(g, ant_pos, ant_wait);
	free(ants_on_path);
	free(ant_pos);
	free(ant_wait);
}
