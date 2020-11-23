#include "str.h"
#include <unistd.h>

void	ft_putendl(const char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}
