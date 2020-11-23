#include <stddef.h>

size_t	ft_chars_count(const char *str, const char c)
{
	register size_t	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str == c)
			++cnt;
		++str;
	}
	return (cnt);
}
