#include "array_list.h"

int	arrlisti_peek(t_arrlisti *list, int *ret, size_t inx)
{
	if (!list || list->size == 0 || inx >= list->size)
		return (0);
	if (ret)
		*ret = list->storage[inx];
	return (1);
}

int	arrlisti_peek_front(t_arrlisti *list, int *ret)
{
	if (!list || list->size == 0)
		return (0);
	if (ret)
		*ret = list->storage[0];
	return (1);
}

int	arrlisti_peek_back(t_arrlisti *list, int *ret)
{
	if (!list || list->size == 0)
		return (0);
	if (ret)
		*ret = list->storage[list->size - 1];
	return (1);
}