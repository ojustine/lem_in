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
	g->coords = hashmap_new();
	g->rooms = arrlist_new(40);
	g->links = arrlist_new(40);
	g->start = ROOM_UNDEFINED;
	g->end = ROOM_UNDEFINED;
}

static void	print_input(t_list *input)
{
	register int		i;

	i = 0;
	while (i < input->size)
	{
		ft_putendl((char*)input->front->data);
		i++;
		input->front = input->front->next;
	}
	ft_putendl("");
}

int			main(int ac, char **av)
{
	t_graph	g;
	t_list	*input;
	t_list	*paths;

	input = list_new();
	graph_init(&g);
	if (ac == 1)
	{
		parse_graph(&g, input);
		paths = dinic(&g);
		//print_paths(paths, &g);
		print_input(input);
		print_solution(&g, paths);
	}
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
}
