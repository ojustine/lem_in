#include <signal.h>
#include <stdlib.h>
#include "util.h"

void	ft_kill(const char *message, const char *cause, const char *func, const char *file)
{
	ft_log_error(message, cause, func, file);
	exit(SIGABRT);
}