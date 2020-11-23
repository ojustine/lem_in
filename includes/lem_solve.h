#ifndef LEM_SOLVE_H
#define LEM_SOLVE_H

#include <list.h>
#include "lem.h"

double			count_turns(t_list *paths, int number_of_ants);
t_list			*get_paths(t_graph *g);
t_list			*dinic(t_graph *g);
void			print_paths(t_list *paths, t_graph *g);

#endif
