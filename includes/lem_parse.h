#ifndef LEM_PARSE_H
# define LEM_PARSE_H

#include "lem.h"
#include "list.h"

typedef enum			e_line_type
{
	LINE_UNDEFINED,
	LINE_EMPTY,
	LINE_ANTS,
	LINE_ROOM,
	LINE_LINK,
	LINE_COMMENT,
	LINE_COMMAND
}						t_line_type;

void	parse_graph(t_graph	*g, t_list *input);
void	parse_room(t_graph *g, t_room_type *type, const char *line);
void	parse_links(t_graph *g, t_room_type *type, const char *line);
void	create_inself_links(t_graph *g);

#endif
