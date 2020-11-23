#include "io.h"
#include "str.h"
#include "util.h"
#include "conv.h"
#include "list.h"
#include "lem_errors.h"

void	parse_ants(t_list *input, int *ants_num)
{
	char		*line;
	long long	num;

	if (get_next_line(0, &line) <= 0)
		ft_kill(LEM_ERR_ANTS, NULL, __func__, __FILE__);
	list_push_back(input, line);
	while (line[0] == '#')
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			ft_kill(LEM_ERR_ANTS, NULL, __func__, __FILE__);
		get_next_line(1, &line);
		list_push_back(input, line);
	}
	num = ft_atol(line);
	if (line[0] == '\0')
		ft_kill(LEM_ERR_EMPTY_LINE, NULL, __func__, __FILE__);
	if (!ft_isint(line) || num < 0)
		ft_kill(LEM_ERR_ANTS, NULL, __func__, __FILE__);
	*ants_num = (int)num;
}
