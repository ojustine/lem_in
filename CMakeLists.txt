cmake_minimum_required(VERSION 3.17)
project(lem C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-O2 -Wall -Wextra")

include_directories(includes sources/libft/inc)

add_library(libft STATIC
		sources/libft/src/mem/memalloc.c
		sources/libft/src/mem/memchr.c
		sources/libft/src/mem/memcmp.c
		sources/libft/src/mem/memcpy.c
		sources/libft/src/mem/memmem.c
		sources/libft/src/mem/memset.c
		sources/libft/src/mem/memswap.c
		sources/libft/inc/array_list.h
		sources/libft/src/array_list/arrlisti_new.c
		sources/libft/src/array_list/arrlisti_peek.c
		sources/libft/src/array_list/arrlisti_pop.c
		sources/libft/src/array_list/arrlisti_push.c
		sources/libft/src/array_list/arrlisti_utils.c
		sources/libft/src/hash_map/hash_map_utils.c
		sources/libft/src/hash_map/hash_map_new.c
		sources/libft/src/hash_map/hash_map_put.c
		sources/libft/src/hash_map/hash_map_resize.c
		sources/libft/src/hash_map/hash_map_get.c
		sources/libft/src/hash_map/hash_map_destroy.c
		sources/libft/src/hash_map/hash_map_iterate.c
		sources/libft/src/util/ft_log_error.c
		sources/libft/src/util/ft_assert.c
		sources/libft/src/util/ft_kill.c
		sources/libft/src/list/list_clear.c
		sources/libft/src/list/list_new.c
		sources/libft/src/list/list_pop.c
		sources/libft/src/list/list_push.c
		sources/libft/src/array_list/arrlist_new.c
		sources/libft/src/array_list/arrlist_peek.c
		sources/libft/src/array_list/arrlist_pop.c
		sources/libft/src/array_list/arrlist_push.c
		sources/libft/src/array_list/arrlist_util.c
		sources/libft/src/string/ft_strlen.c
		sources/libft/src/string/ft_strchr.c
		sources/libft/src/string/ft_strndup.c
		sources/libft/src/string/ft_strnlen.c
		sources/libft/src/string/ft_strdup.c
		sources/libft/src/string/ft_strjoin.c
		sources/libft/src/string/ft_strsplit.c
		sources/libft/src/string/ft_words_count.c
		sources/libft/src/string/ft_free_split.c
		sources/libft/src/string/ft_chars_count.c
		sources/libft/src/string/ft_strequ.c
		sources/libft/src/string/ft_isint.c
		sources/libft/src/io/ft_putnbr.c
		sources/libft/src/io/ft_putstr.c
		sources/libft/src/io/ft_putendl.c
		sources/libft/src/io/get_next_line.c
		sources/libft/src/conv/ft_atol.c
		sources/libft/src/math/ft_min.c)

set_target_properties(libft PROPERTIES PUBLIC_HEADER
		sources/libft/inc/hash_map.h
		sources/libft/inc/str.h
		sources/libft/inc/list.h
		sources/libft/inc/util.h
		sources/libft/inc/io.h
		sources/libft/inc/conv.h
		sources/libft/inc/math.h)

add_executable(lem $<TARGET_OBJECTS:libft>
		includes/lem_structs.h
		includes/lem_errors.h
		includes/lem_parse.h
		includes/lem_solve.h
		includes/lem_paths.h
		includes/lem_free.h
		sources/main.c
		sources/parse.c
		sources/parse_rooms.c
		sources/parse_links.c
		sources/solve.c
		sources/paths_get.c
		sources/paths_print.c
		sources/paths_sort.c
		sources/free.c)
