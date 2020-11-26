#include <stdlib.h>
#include "lem_structs.h"
#include "io.h"
#include "util.h"
#include "hash_map.h"
#include "lem_parse.h"
#include "lem_errors.h"
#include "lem_paths.h"
#include "lem_solve.h"
#include "lem_free.h"

static t_graph	*new_graph(void)
{
	t_graph *g;

	g = malloc(sizeof(t_graph));
	ft_assert(g != NULL, __func__, "malloc error");
	g->rooms_names = hashmap_new();
	g->coords = hashmap_new();
	g->rooms = arrlist_new(100);
	g->links = arrlist_new(100);
	ft_assert(g->rooms_names != NULL
			&& g->coords != NULL
			&& g->rooms != NULL
			&& g->links != NULL,
			__func__, "malloc error");
	g->start = ROOM_UNDEFINED;
	g->end = ROOM_UNDEFINED;
	return (g);
}

static void		print_input(t_list *input)
{
	register t_list_node	*node;

	if (input->size == 0)
		return ;
	node = input->front;
	while (node != NULL)
	{
		ft_putstr(node->data);
		ft_putstr("\n");
		node = node->next;
	}
	ft_putstr("\n");
}

int			main(int ac, char **av)
{
	t_graph	*g;
	t_list	*input;
	t_list	*paths;

	input = list_new();
	ft_assert(input != NULL, __func__, "malloc error");
	g = new_graph();
	if (ac == 1)
	{
		parse_graph(g, input);
		paths = solve(g);
		if (!paths)
			ft_kill(LEM_ERR_NO_PATHS, NULL, __func__, __FILE__);
		print_input(input);
		print_paths(g, paths);
		list_clear(&paths, free_path);
		list_clear(&input, free);
		free_graph(&g);
	}
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
}
