#ifndef UTIL_H
# define UTIL_H

void	ft_log_error(const char *message, const char *cause, const char *func, const char *file);
void	ft_assert(int to_check, const char *func, const char *message);
void	ft_kill(const char *message, const char *cause, const char *func, const char *file);

#endif
