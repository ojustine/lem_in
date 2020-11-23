#include "hash_map.h"

void	*hashmap_iter(t_hashmap *hmap, size_t *iter, void **val_ptr)
{
	const size_t				capacity = hmap->capacity;
	register size_t				i;
	register t_hashmap_entry	*entry;

	i = *iter;
	while (i < capacity)
	{
		entry = &hmap->storage[i];
		i++;
		if (!entry->key)
			continue;
		*iter = i;
		if (val_ptr)
			*val_ptr = entry->val;
		return (entry->key);
	}
	return (NULL);
}
