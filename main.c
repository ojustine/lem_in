#include "lem.h"
#include "mem.h"
#include "str.h"
#include "io.h"
#include "hash_map.h"
#include "lem_parse.h"
#include "lem_solve.h"

int main(int ac, char **av)
{
	t_graph g;
	t_list *input;
	t_list *paths;

	input = list_new();
	if (ac == 1)
	{
		parse_graph(&g, input);
		paths = dinic(&g);
		print_paths(paths, &g);
	}
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
}
