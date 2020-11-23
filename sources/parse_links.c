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
	list_push_back(((t_room *)g->rooms->storage[from])->links, (void *)g->links->size);
	arrlist_push_back(g->links, e_dir);
	list_push_back(((t_room *)g->rooms->storage[to])->links, (void *)g->links->size);
	arrlist_push_back(g->links, e_rev);
}

static void		validate_link_line(t_graph *g, char **words)
{
	if (!hashmap_get(g->links_names, words[0], ft_strlen(words[0]))
	|| !hashmap_get(g->links_names, words[1], ft_strlen(words[1])))
		ft_kill(LEM_ERR_LINK_NO_ROOM, NULL, __func__, __FILE__);
	if (ft_strequ(hashmap_get(g->links_names, words[0], ft_strlen(words[0])),
		words[1])
		|| ft_strequ(hashmap_get(g->links_names, words[1], ft_strlen(words[1])),
		words[0]))
		ft_kill(LEM_ERR_LINK_DUP, NULL, __func__, __FILE__);
	hashmap_put(g->links_names, words[0], ft_strlen(words[0]), words[1]);
	hashmap_put(g->links_names, words[1], ft_strlen(words[1]), words[0]);//todo
}

static void		handle_link(t_graph *g, char **words)
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

void		add_split_links(t_graph *g)
{
	size_t	from;
	size_t	to;

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

	if (*type)
		ft_kill(LEM_ERR_ROOM_INV_COMMAND, NULL, __func__, __FILE__);
	words = ft_strsplit(line, '-');
	handle_link(g, words);
	//add_split_links(g);
}

