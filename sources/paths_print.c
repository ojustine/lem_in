#include "io.h"
#include "str.h"
#include "lem_structs.h"
#include "mem.h"
#include "util.h"
#include "list.h"
#include "lem_errors.h"
#include "lem_paths.h"

static void			print_ant_turn(int ant, char *room_name)
{
	ft_putstr("L");
	ft_putnbr(ant);
	ft_putstr("-");
	ft_putstr(room_name);
}

static void			print_paths_do(t_graph *g, t_solution *sol)
{
	int cur_ant;
	int printed;
	int room_index;

	while (1)
	{
		printed = 0;
		cur_ant = -1;
		while (++cur_ant < g->ants)
			if (sol->ants[cur_ant].wait_turns != 0)
				sol->ants[cur_ant].wait_turns--;
			else if (sol->ants[cur_ant].path != NULL)
			{
				if (printed == 1)
					ft_putstr(" ");
				printed = 1;
				room_index = (int)(long long)(sol->ants[cur_ant].path)->data;
				print_ant_turn(cur_ant + 1,
					((t_room *)g->rooms->storage[room_index])->name);
				sol->ants[cur_ant].path = sol->ants[cur_ant].path->next;
			}
		if (!printed)
			break ;
		ft_putstr("\n");
	}
}

static void			set_ants_on_paths(t_graph *g, t_solution *sol)
{
	t_list_node *node;
	int			i;
	int			j;

	i = 0;
	while (i < g->ants)
	{
		j = 0;
		node = sol->paths->front;
		while ((size_t)j < sol->paths->size - 1)
		{
			if (sol->paths_sizes[j] < sol->paths_sizes[j + 1])
				break;
			j++;
			node = node->next;
		}
		sol->paths_sizes[j]++;
		sol->ants[i].wait_turns = sol->paths_waits[j]++;
		sol->ants[i].path = ((t_list *)node->data)->front;
		i++;
	}
}

static t_solution	*build_solution(t_graph *g, t_list *paths)
{
	t_solution	*sol;
	t_list_node	*node;
	size_t		i;

	sol = malloc(sizeof(t_solution));
	ft_assert(sol != NULL, __func__, "malloc error");
	sol->ants = ft_calloc(g->ants, sizeof(t_ant));
	sol->paths_sizes = ft_calloc(paths->size, sizeof(size_t));
	sol->paths_waits = ft_calloc(paths->size, sizeof(size_t));
	ft_assert(sol->ants != NULL && sol->paths_sizes != NULL &&
			  sol->paths_waits != NULL, __func__, "malloc error");
	sort_paths(paths);
	sol->paths = paths;
	node = sol->paths->front;
	i = 0;
	while (i < paths->size)
	{
		sol->paths_sizes[i++] = ((t_list *)(node->data))->size;
		node = node->next;
	}
	set_ants_on_paths(g, sol);
	return (sol);
}

void				print_paths(t_graph *g, t_list *paths)
{
	t_solution	*sol;

	sol = build_solution(g, paths);
	print_paths_do(g, sol);
	free(sol->ants);
	free(sol->paths_sizes);
	free(sol->paths_waits);
	free(sol);
}
