#include <stdio.h>
#include <fcntl.h>
//#include <io.h>
#include "lem.h"
#include "mem.h"
#include "str.h"
#include "io.h"
#include "hash_map.h"
#include "lem_parse.h"
#include "lem_solve.h"

static char *rand_string(char *str, size_t size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK.1234567890";
	if (size)
	{
		--size;
		for (size_t n = 0; n < size; n++)
		{
			int key = rand() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

int main(int ac, char **av)
{
	char *test = "test";
	char line[11];
	t_graph g;
	t_list *input;
	t_list *paths;

//	t_hashmap *map = hashmap_new();
//	srand(0);
//	for (int i = 0; i < 4000; i++)
//	{
//		rand_string(line, 11);
//		hashmap_put(map, line, 10, test);
//		if (!hashmap_get(map, line, 10))
//			printf("%s\n", line);
//	}
//	size_t iter = 0;
//	void *val;
//	void *key;
//	while (hashmap_iter(map, &iter, &key, &val))
//		printf("%llu %s\n", iter, (char*)key);
//	srand(0);
//	for (int i = 0; i < 4000; i++)
//	{
//		rand_string(line, 11);
//		//hashmap_put(map, line, 10, test);
//		if (!hashmap_get(map, line, 10))
//			printf("%d %s\n", i, line);
//	}
	input = list_new();
	if (ac == 1)
	{
		parse_graph(&g, input);
		paths = dinic(&g);
		//print_paths(paths, &g);
		print_solution(&g, paths);
	}
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
}
