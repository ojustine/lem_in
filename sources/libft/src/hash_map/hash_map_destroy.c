#include <stdlib.h>
#include "hash_map.h"

void	hashmap_destroy(t_hashmap **hmap)
{
	register size_t 			i;
	register t_hashmap_entry	*entry;

	i = 0;
	while (i < (const size_t)(*hmap)->capacity)
	{
		entry = &(*hmap)->storage[i++];
		if (entry->key)
			free(entry->key);
	}
	free((*hmap)->storage);
	free(*hmap);
	*hmap = NULL;
}
