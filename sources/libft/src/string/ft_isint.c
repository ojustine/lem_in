#include <limits.h>
#include "str.h"
#include "conv.h"

int	ft_isint(char *str)
{
	const long long	nb = ft_atol(str);

	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0' || (*str == '0' && *(str + 1) != '\0'))
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	if (nb < INT_MIN || nb > INT_MAX)
		return (0);
	return (1);
}
