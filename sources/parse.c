#include <stdlib.h>
#include "io.h"
#include "str.h"
#include "lem.h"
#include "util.h"
#include "list.h"
#include "lem_errors.h"
#include "lem_parse.h"

static inline void	parse_command(const char *line, t_room_type *command)
{
	if (ft_strequ(line, "##start"))
		*command = ROOM_START;
	else if (ft_strequ(line, "##end"))
		*command = ROOM_END;
}

static inline int	is_command(const char *line)
{
	return (*line == '#' && *(line + 1) == '#');
}

static inline int	is_room(const char *line)
{
	return (ft_words_count(line, ' ') == 3);
}

static inline int	is_link(const char *line)
{
	return (ft_words_count(line, '-') == 2 && ft_chars_count(line, '-') == 1);
}

static void		info_init(t_graph *g)
{
	g->rooms_names = hashmap_new();
	g->links_names = hashmap_new();
	g->coords = hashmap_new();
	g->rooms = arrlist_new(40);
	g->links = arrlist_new(40);
	g->start = 0;
	g->end = 0;
//	info->n = rooms->size;
//	g->last = malloc(info->n * sizeof(t_list_node *));
//	if (info->d == NULL || info->last == NULL)
//	{
//		ft_throw(ALLOC_MSG, E_ALLOC);
//	}
}

void				parse_graph(t_graph	*g, t_list *input)
{
	t_room_type	command;
	char		*line;

	command = ROOM_DEFAULT;
	info_init(g);
	parse_ants(input, &g->ants);
	while (get_next_line(0, &line))
	{
		list_push_back(input, line);
		if (*line == '\0')
			ft_kill(LEM_ERR_EMPTY_LINE, NULL, __func__, __FILE__);
		else if (*line == '#' && *(line + 1) != '#')
			continue ;
		else if (is_command(line) && command == ROOM_DEFAULT)
			parse_command(line, &command);
		else if (is_room(line))
			parse_room(g, &command, line);
		else if (is_link(line) && command == ROOM_DEFAULT)
			parse_links(g, &command, line);
		else
			ft_kill(LEM_ERR_INV_LINE, NULL, __func__, __FILE__);
	}
	g->n = g->rooms->size;
	g->last = malloc(g->n * sizeof(t_list_node *));
	add_split_links(g);
}