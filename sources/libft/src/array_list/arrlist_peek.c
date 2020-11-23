#include "array_list.h"
#include "util.h"


void	*arrlist_peek(t_arrlist *list, size_t inx)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	ft_assert(list->size != 0 && inx < list->size, __func__, ARRLIST_ERR_INDEX);
	return (list->storage[inx]);
}

void	*arrlist_peek_front(t_arrlist *list)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	ft_assert(list->size != 0, __func__, ARRLIST_ERR_INDEX);

	return (list->storage[0]);
}

void	*arrlist_peek_back(t_arrlist *list)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	ft_assert(list->size != 0, __func__, ARRLIST_ERR_INDEX);

	return (list->storage[list->size - 1]);
}
