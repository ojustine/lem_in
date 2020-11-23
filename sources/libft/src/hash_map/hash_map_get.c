#include "hash_map.h"
#include "mem.h"

void	*hashmap_get(t_hashmap *hmap, const void *key, size_t key_len)
{
	uint64_t					hash;
	register size_t				offset;
	register size_t				i;
	register t_hashmap_entry	*bucket;

	if (!key || !key_len)
		return (NULL);
	hash = murmur_hash_64(key, key_len, hmap->hash_key);
	i = hash * hmap->hash_key & (hmap->capacity - 1);
	offset = 0;
	while (offset <= hmap->max_offset)
	{
		bucket = &hmap->storage[i];
		if (!bucket->key)
			return NULL;
		if (bucket->hash == hash && bucket->key_len == key_len &&
			ft_memcmp(bucket->key, key, key_len) == 0)
			return bucket->val;
		if (++i == hmap->capacity)
			i = 0;
		offset++;
	}
	return (NULL);
}
