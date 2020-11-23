#ifndef LEM_PARSE_H
# define LEM_PARSE_H

#include "lem.h"
#include "list.h"

void	parse_ants(t_list *input, int *ants_num);
void	parse_graph(t_graph	*g, t_list *input);
void	parse_room(t_graph *g, t_room_type *type, const char *line);
void	parse_links(t_graph *g, t_room_type *type, const char *line);
void	add_split_links(t_graph *g);

#endif
