#include "list.h"

void	sort_paths(t_list *paths)
{
	t_list_node	*left;
	t_list_node	*right;
	void		*data;

	left = paths->front;
	while (left != NULL)
	{
		right = left->next;
		while (right != NULL)
		{
			if (((t_list *)left->data)->size > ((t_list *)right->data)->size)
			{
				data = left->data;
				left->data = right->data;
				right->data = data;
			}
			right = right->next;
		}
		left = left->next;
	}
}
