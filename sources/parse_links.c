#include <stdlib.h>
#include "lem.h"
#include "str.h"
#include "util.h"
#include "conv.h"
#include "list.h"
#include "hash_map.h"
#include "lem_errors.h"

static void		add_edge(t_graph *g, size_t from, size_t to)
{
	t_link	*e_dir;
	t_link	*e_rev;

	e_dir = malloc(sizeof(t_link));
	e_rev = malloc(sizeof(t_link));
	ft_assert(e_dir != NULL && e_rev != NULL, __func__, "malloc error");
	e_dir->from = from;
	e_dir->to = to;
	e_dir->cap = 1;
	e_dir->flow = 0;
	e_rev->from = to;
	e_rev->to = from;
	e_rev->cap = 0;
	e_rev->flow = 0;
	list_push_back(((t_room *)arrlist_peek(g->rooms, from))->links, (void *)g->links->size);
	arrlist_push_back(g->links, e_dir);
	list_push_back(((t_room *)arrlist_peek(g->rooms, to))->links, (void *)g->links->size);
	arrlist_push_back(g->links, e_rev);
}

static void		validate_link_line(t_graph *g, char **words)
{
	t_room *from;
	t_room *to;
	t_list_node	*node;

	from = hashmap_get(g->rooms_names, words[0], ft_strlen(words[0]));
	to = hashmap_get(g->rooms_names, words[1], ft_strlen(words[1]));
	if (!from || !to)
		ft_kill(LEM_ERR_LINK_NO_ROOM, NULL, __func__, __FILE__);
	node = from->links->front;
	for (int i = 0; i < from->links->size; i++)
	{
		if (((t_link *)(g->links->storage[(size_t)node->data]))->to == to->index)
			ft_kill(LEM_ERR_LINK_DUP, NULL, __func__, __FILE__);
		node = node->next;
	}
	node = to->links->front;
	for (int i = 0; i < to->links->size; i++)
	{
		if (((t_link *)(g->links->storage[(size_t)node->data]))->from == from->index)
			ft_kill(LEM_ERR_LINK_DUP, NULL, __func__, __FILE__);
		node = node->next;
	}
//
//
//	if (ft_strequ(hashmap_get(g->links_names, words[0], ft_strlen(words[0])),
//		words[1])
//		|| ft_strequ(hashmap_get(g->links_names, words[1], ft_strlen(words[1])),
//		words[0]))
//		ft_kill(LEM_ERR_LINK_DUP, NULL, __func__, __FILE__);
//	hashmap_put(g->links_names, words[0], ft_strlen(words[0]), words[1]);
//	hashmap_put(g->links_names, words[1], ft_strlen(words[1]), words[0]);
}

static void		create_link(t_graph *g, char **words)
{
	size_t	from;
	size_t	to;
	t_room	*room_from;
	t_room	*room_to;

	room_from = (t_room *)hashmap_get(g->rooms_names, words[0], ft_strlen(words[0]));
	from = room_from->index + 1;
	room_to = (t_room *)hashmap_get(g->rooms_names, words[1], ft_strlen(words[1]));
	to = room_to->index;
	add_edge(g, from, to);
	add_edge(g, to + 1, from - 1);
}

void			create_inself_links(t_graph *g)
{
	register size_t	from;
	register size_t	to;

	from = 0;
	to = 1;
	while (to < g->rooms->size)
	{
		add_edge(g, from, to);
		add_edge(g, to, from);
		from += 2;
		to += 2;
	}
}

void			parse_links(t_graph *g, t_room_type *type, const char *line)
{
	char **words;

	if (*type != ROOM_DEFAULT)
		ft_kill(LEM_ERR_ROOM_INV_COMMAND, NULL, __func__, __FILE__);
	words = ft_strsplit(line, '-');
	validate_link_line(g, words);
	create_link(g, words);
}
