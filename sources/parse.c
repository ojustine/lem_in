#include "conv.h"
#include "io.h"
#include "str.h"
#include "lem_structs.h"
#include "util.h"
#include "list.h"
#include "lem_errors.h"
#include "lem_parse.h"

static t_line_type	get_line_type(char *line)
{
	static int first_line = 1;

	if (*line == '#' && *(line + 1) != '#')
		return (LINE_COMMENT);
	else if (!first_line)
	{
		if (*line == '#' && *(line + 1) == '#')
			return (LINE_COMMAND);
		else if (ft_words_count(line, ' ') == 3)
			return (LINE_ROOM);
		else if (ft_words_count(line, '-') == 2
		&& ft_chars_count(line, '-') == 1)
			return (LINE_LINK);
	}
	else if (ft_isint(line))
	{
		first_line = 0;
		return (LINE_ANTS);
	}
	else if (!*line)
		ft_kill(LEM_ERR_EMPTY_LINE, NULL, __func__, __FILE__);
	return (LINE_UNDEFINED);
}

static void			check_start_end(t_graph *g)
{
	if (g->start == ROOM_UNDEFINED)
		ft_kill(LEM_ERR_NO_START, NULL, __func__, __FILE__);
	if (g->end == ROOM_UNDEFINED)
		ft_kill(LEM_ERR_NO_END, NULL, __func__, __FILE__);
}

static inline void	parse_command(const char *line, t_room_type *command)
{
	if (ft_strequ(line, "##start"))
		*command = ROOM_START;
	else if (ft_strequ(line, "##end"))
		*command = ROOM_END;
	else
		*command = ROOM_DEFAULT;
}

void				parse_ants(char *line, int *ants)
{
	long long	num;

	num = ft_atol(line);
	if (!ft_isint(line) || num < 0)
		ft_kill(LEM_ERR_ANTS, NULL, __func__, __FILE__);
	*ants = (int)num;
}

void				parse_graph(t_graph *g, t_list *input)
{
	t_line_type	line_type;
	t_room_type	command;
	char		*line;

	command = ROOM_DEFAULT;
	while (get_next_line(0, &line) > 0)
	{
		line_type = get_line_type(line);
		list_push_back(input, line);
		if (line_type == LINE_COMMENT)
			continue ;
		else if (line_type == LINE_ANTS)
			parse_ants(line, &g->ants);
		else if (line_type == LINE_COMMAND)
			parse_command(line, &command);
		else if (line_type == LINE_ROOM)
			parse_room(g, &command, line);
		else if (line_type == LINE_LINK && command == ROOM_DEFAULT)
			parse_links(g, &command, line);
		else
			ft_kill(LEM_ERR_INV_LINE, NULL, __func__, __FILE__);
	}
	check_start_end(g);
	create_inself_links(g);
}