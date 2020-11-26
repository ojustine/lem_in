#include <stdlib.h>
#include "lem.h"
#include "str.h"
#include "util.h"
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
	list_push_back(((t_room *)arrlist_peek(g->rooms, from))->links,
		(void *)g->links->size);
	arrlist_push_back(g->links, e_dir);
	list_push_back(((t_room *)arrlist_peek(g->rooms, to))->links,
		(void *)g->links->size);
	arrlist_push_back(g->links, e_rev);
}

static void		validate_link_duplicates(t_graph *g, char **words)
{
	t_room *from;
	t_room *to;
	t_list_node	*links;
	size_t	to_i;
	char	*to_name;

	from = hashmap_get(g->rooms_names, words[0], ft_strlen(words[0]));
	to = hashmap_get(g->rooms_names, words[1], ft_strlen(words[1]));
	if (!from || !to)
		ft_kill(LEM_ERR_LINK_NO_ROOM, NULL, __func__, __FILE__);
	links = from->links->front;
	while (links != NULL)
	{
		to_i = ((t_link *)(g->links->storage[(size_t)links->data]))->to;
		to_name = ((t_room *)(g->rooms->storage[to_i]))->name;
		if (ft_strequ(to->name, to_name))
			ft_kill(LEM_ERR_LINK_DUP, NULL, __func__, __FILE__);
		links = links->next;
	}
}

static void		create_link(t_graph *g, char **words)
{
	size_t	from_index;
	size_t	to_index;
	t_room	*from;
	t_room	*to;

	from = (t_room *)hashmap_get(g->rooms_names, words[0], ft_strlen(words[0]));
	to = (t_room *)hashmap_get(g->rooms_names, words[1], ft_strlen(words[1]));
	from_index = from->index + 1;
	to_index = to->index;
	add_edge(g, from_index, to_index);
	add_edge(g, to_index + 1, from_index - 1);
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
	validate_link_duplicates(g, words);
	create_link(g, words);
	ft_free_split(words);
}
