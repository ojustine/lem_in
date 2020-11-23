#include "hash_map.h"
#include "mem.h"

void	hashmap_init_new_storage(t_hashmap *hmap, size_t new_capacity)
{
	new_capacity = next_power_of_two(new_capacity);
	hmap->storage = ft_calloc(new_capacity, sizeof(t_hashmap_entry));
	//todo assert new_capacity > hmap->size && new_storage != null
	hmap->capacity = new_capacity;
	hmap->max_size = new_capacity * hmap->load_factor;
	hmap->max_offset = ft_log2(new_capacity);
	hmap->size = 0;
}

int		hashmap_resize(t_hashmap *hmap, size_t new_capacity)
{
	register size_t				i;
	const size_t				old_capacity = hmap->capacity;
	register t_hashmap_entry	*entry;
	t_hashmap_entry				*old_storage;
	t_hashmap					snapshot;

	snapshot = *hmap;
	old_storage = hmap->storage;
	hashmap_init_new_storage(hmap, new_capacity);
	i = 0;
	while (i < old_capacity)
	{
		entry = &old_storage[i++];
		if (!entry->key)
			continue;
		if (!hashmap_insert(hmap, entry->key, entry->key_len, entry->val))
		{
			free(hmap->storage);
			*hmap = snapshot;
			return (0);
		}
		free(entry->key);
	}
	free(old_storage);
	return (1);
}
