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
						ROOM_IN = 11,
						ROOM_OUT = 31,
}						t_room_type;

typedef enum			e_link_type
{
						BLOCKED,
						ALLOWED,
						INNER
}						t_link_type;

typedef struct			s_link
{
	int					from;
	int					to;
	int					cap;
	int					flow;
	enum e_link_type	type;
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
