#include "hash_map.h"

void	*hashmap_iter(t_hashmap *hmap, size_t *iter, void **keyp, void **valp)
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
		if (keyp)
			*keyp = entry->key;
		if (valp)
			*valp = entry->val;
		return (entry->key);
	}
	return (NULL);
}
