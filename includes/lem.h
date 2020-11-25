#ifndef LEM_H
#define LEM_H

# include <stddef.h>
# include "array_list.h"
# include "list.h"
# include "hash_map.h"

typedef enum			e_room_type
{
						ROOM_DEFAULT,
						ROOM_START,
						ROOM_END,
}						t_room_type;

typedef struct			s_ant
{
	int					wait_turns;
	t_list_node			*path;
}						t_ant;

typedef struct			s_link
{
	int					from;
	int					to;
	int					cap;
	int					flow;
}						t_link;

typedef struct			s_room
{
	enum e_room_type	type;
	char				*name;
	size_t				index;
	int					x;
	int					y;
	t_list				*links;
}						t_room;

typedef struct	s_graph
{
	t_hashmap	*rooms_names;
	t_hashmap	*links_names;
	t_hashmap	*coords;
	t_arrlist	*rooms;
	t_arrlist	*links;
	t_list_node	**last;
	int			n;
	int			ants;
	int			start;
	int			end;
}				t_graph;

#endif
