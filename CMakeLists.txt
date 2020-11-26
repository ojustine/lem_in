cmake_minimum_required(VERSION 3.17)
project(lem C)

set(CMAKE_C_STANDARD 99)

include_directories(includes sources/libft/inc)

add_executable(lem main.c
		sources/libft/src/mem/memalloc.c
		sources/libft/src/mem/memchr.c
		sources/libft/src/mem/memcmp.c
		sources/libft/src/mem/memcpy.c
		sources/libft/src/mem/memmem.c
		sources/libft/src/mem/memset.c
		sources/libft/src/mem/memswap.c
		sources/libft/inc/array_list.h
		sources/libft/src/array_list/arrlisti_new.c sources/libft/src/array_list/arrlisti_peek.c sources/libft/src/array_list/arrlisti_pop.c sources/libft/src/array_list/arrlisti_push.c sources/libft/src/array_list/arrlisti_utils.c includes/lem.h sources/libft/src/hash_map/hash_map_utils.c sources/libft/inc/hash_map.h sources/libft/src/hash_map/hash_map_new.c sources/libft/src/hash_map/hash_map_put.c sources/libft/src/hash_map/hash_map_resize.c sources/libft/src/hash_map/hash_map_get.c sources/libft/src/hash_map/hash_map_destroy.c sources/libft/src/hash_map/hash_map_iterate.c sources/parse.c sources/libft/src/io/ft_putendl.c sources/libft/inc/str.h sources/libft/src/string/ft_strlen.c sources/libft/inc/list.h sources/libft/src/list/list_clear.c sources/libft/src/list/list_new.c sources/libft/src/list/list_pop.c sources/libft/src/list/list_push.c sources/libft/src/util/ft_log_error.c sources/libft/inc/util.h sources/libft/src/util/ft_assert.c sources/libft/src/array_list/arrlist_new.c sources/libft/src/array_list/arrlist_peek.c sources/libft/src/array_list/arrlist_pop.c sources/libft/src/array_list/arrlist_push.c sources/libft/src/array_list/arrlist_util.c sources/libft/inc/io.h sources/libft/src/io/get_next_line.c sources/libft/src/string/ft_strchr.c sources/libft/src/string/ft_strndup.c sources/libft/src/string/ft_strnlen.c sources/libft/src/string/ft_strdup.c sources/libft/src/string/ft_strjoin.c includes/lem_errors.h sources/libft/src/util/ft_kill.c sources/libft/src/string/ft_strsplit.c sources/libft/src/string/ft_words_count.c sources/libft/src/string/ft_free_split.c sources/libft/src/conv/ft_atol.c sources/libft/inc/conv.h includes/lem_parse.h sources/libft/src/string/ft_chars_count.c sources/libft/src/string/ft_strequ.c sources/libft/src/string/ft_isint.c sources/parse_rooms.c sources/parse_links.c sources/solve.c sources/paths_get.c includes/lem_solve.h sources/paths_print.c)