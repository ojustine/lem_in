#ifndef LEM_PATHS_H
# define LEM_PATHS_H

# include "list.h"

void			sort_paths(t_list *paths);
double			paths_avg_turns(t_list *paths, int number_of_ants);
t_list			*get_paths(t_graph *g);
void			print_paths(t_graph *g, t_list *paths);

#endif
