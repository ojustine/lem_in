#include <signal.h>
#include <stdlib.h>
#include "util.h"

void	ft_assert(int to_check, const char *func, const char *message)
{
	if (!to_check)
	{
		ft_log_error(message, "ASSERTION", func, NULL);
		exit(SIGABRT);
	}
}