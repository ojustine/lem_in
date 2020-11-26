#include <stdlib.h>
#include "lem.h"
#include "str.h"
#include "util.h"
#include "conv.h"
#include "list.h"
#include "hash_map.h"
#include "lem_errors.h"

static int		validate_room_line(char **words)
{
	char		*name;

	name = words[0];
	if (*name == 'L')
		ft_kill(LEM_ERR_ROOM_INV_NAME, NULL, __func__, __FILE__);
	while (*name)
	{
		if ('!' > *name || *name > '~' || *name == '-')
			ft_kill(LEM_ERR_ROOM_INV_NAME, NULL, __func__, __FILE__);
		++name;
	}
	if (words[1][0] == '\0' || !ft_isint(words[1]))
		ft_kill(LEM_ERR_ROOM_COORDS, NULL, __func__, __FILE__);
	if (words[2][0] == '\0' || !ft_isint(words[2]))
		ft_kill(LEM_ERR_ROOM_COORDS, NULL, __func__, __FILE__);
	return (1);
}

static t_room	*new_room(char **words, size_t idx, const t_room_type *type)
{
	t_room	*room;

	room = malloc(sizeof(t_room));
	ft_assert(room != NULL, __func__, "malloc error");
	room->name = words[0];
	room->x = (int)ft_atol(words[1]);
	room->y = (int)ft_atol(words[2]);
	room->index = idx;
	room->type = *type;
	room->links = list_new();
	return (room);
}

static void		create_room(t_graph *g, const t_room_type *type, char **words)
{
	t_room			*room_in;
	t_room			*room_out;
	int				*coord_y;
	static size_t	index;

	room_in = new_room(words, index++, type);
	room_out = new_room(words, index++, type);
	coord_y = (int *)hashmap_get(g->coords, &room_in->x, sizeof(int));
	if (hashmap_get(g->rooms_names, room_in->name, ft_strlen(room_in->name)))
		ft_kill(LEM_ERR_ROOM_DUP_NAME, NULL, __func__, __FILE__);
	if (coord_y && *coord_y == room_in->y)
		ft_kill(LEM_ERR_ROOM_DUP_COORD, NULL, __func__, __FILE__);
	arrlist_push_back(g->rooms, room_in);
	arrlist_push_back(g->rooms, room_out);
	hashmap_put(g->coords, &room_in->x, sizeof(int), &room_in->y);
	hashmap_put(g->rooms_names, room_in->name, ft_strlen(room_in->name),
	g->rooms->storage[index - 2]);
	if (*type == ROOM_START)
		g->start = (int)index - 1;
	if (*type == ROOM_END)
		g->end = (int)index - 2;
}

void			parse_room(t_graph *g, t_room_type *type, const char *line)
{
	char	**words;

	words = ft_strsplit(line, ' ');
	validate_room_line(words);
	if (*type == ROOM_START && g->start > 0
	|| *type == ROOM_END && g->end > 0)
		ft_kill(LEM_ERR_ROOM_DUP_COMMAND, NULL, __func__, __FILE__);
	create_room(g, type, words);
	*type = ROOM_DEFAULT;
}
