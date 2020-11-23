#include "mem.h"
#include "hash_map.h"

static inline int	hashmap_insert_try(t_hashmap *hmap, t_hashmap_entry *bucket,
					t_hashmap_entry *entry)
{
	t_hashmap_entry	tmp;

	if (!bucket->key)
	{
		*bucket = *entry;
		hmap->size++;
		return (1);
	}
	if (bucket->hash == entry->hash && bucket->key_len == entry->key_len &&
		ft_memcmp(bucket->key, entry->key, entry->key_len) == 0)
	{
		free(entry->key);
		bucket->val = entry->val;
		return (1);
	}
	if (entry->offset > bucket->offset)
	{
		tmp = *entry;
		*entry = *bucket;
		*bucket = tmp;
	}
	return (0);
}

int					hashmap_insert(t_hashmap *hmap, const void *key,
					size_t key_len, void *val)
{
	t_hashmap_entry *bucket;
	t_hashmap_entry entry;
	register size_t	i;

	entry.key = malloc(key_len);
	//todo assert malloc && i < size
	ft_memcpy(entry.key, key, key_len);
	entry.hash = murmur_hash_64(key, key_len, hmap->hash_key);
	entry.key_len = key_len;
	entry.val = val;
	entry.offset = 0;
	i = entry.hash * hmap->hash_key & (hmap->capacity - 1);
	while (entry.offset <= hmap->max_offset)
	{
		bucket = &hmap->storage[i];
		if (hashmap_insert_try(hmap, bucket, &entry))
			return (1);
		if (++i == hmap->capacity)
			i = 0;
		entry.offset++;
	}
	return (0);
}

int	hashmap_put(t_hashmap *hmap, const void *key, size_t key_len, void *val)
{
	size_t	try;

	if (!key || !key_len)
		return (0);
	if (hmap->size == hmap->max_size)
	{
		try = 0;
		while (!hashmap_resize(hmap, hmap->capacity << 1U))
		{
			try++;
			//todo assert try < some num?
			//todo hash_key = next_prime_num
		}
	}
	return (hashmap_insert(hmap, key, key_len, val));
}
