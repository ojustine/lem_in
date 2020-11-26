#include <stdio.h>
#include <fcntl.h>
#include "lem.h"
#include "mem.h"
#include "str.h"
#include "io.h"
#include "hash_map.h"
#include "lem_parse.h"
#include "lem_solve.h"

static void	graph_init(t_graph *g)
{
	g->rooms_names = hashmap_new();
	g->links_names = hashmap_new();
	g->coords = hashmap_new();
	g->rooms = arrlist_new(40);
	g->links = arrlist_new(40);
	g->start = 0;
	g->end = 0;
}

int			main(int ac, char **av)
{
	t_graph g;
	t_list *input;
	t_list *paths;

	input = list_new();
	graph_init(&g);
	if (ac == 1)
	{
		parse_graph(&g, input);
		paths = dinic(&g);
		print_paths(paths, &g);
		print_solution(&g, paths);
	}
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
}
