#include <stdlib.h>
#include "hash_map.h"
#include "mem.h"

//todo add flags: copy val, copy key, auto increase, auto decrease
//todo prime num for every po2
t_hashmap	*hashmap_new_param(size_t capacity, float load_factor, size_t hash_key)
{
	t_hashmap	*hmap;

	capacity = next_power_of_two(capacity);
	hmap = ft_calloc(1, sizeof(t_hashmap));
	if (!hmap)
		return (NULL);
	hmap->load_factor = load_factor;
	hmap->hash_key = hash_key;
	if (!hashmap_resize(hmap, capacity))
	{
		free(hmap);
		return (NULL);
	}
	return (hmap);
}

t_hashmap	*hashmap_new(void)
{
	return (hashmap_new_param(64, 0.72f, 137));
}
