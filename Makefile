NAME = lem-in
LIBFT_A = sources/libft/libft.a

CC = gcc
FLAGS =

LIBFT_DIR = sources/libft


SRC_DIR = sources
OBJ_DIR = obj

INCLUDE = -I./includes
INCLUDE += -I./sources/libft/inc

HEADERS = includes/lem.h
HEADERS += includes/lem_errors.h
HEADERS += includes/lem_parse.h
HEADERS += includes/lem_solve.h


SRCS = main.c
SRCS += parse.c
SRCS += parse_links.c
SRCS += parse_rooms.c
SRCS += paths_get.c
SRCS += paths_print.c
SRCS += solve.c

OBJS = $(SRCS:.c=.o)

SRCS_PATH = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS_PATH = $(addprefix $(OBJ_DIR)/,$(OBJS))


.PHONY: clean fclean all re make_lib

all: $(NAME)

$(LIBFT_A) : make_lib
	@mkdir -p $(OBJ_DIR)

make_lib:
	$(MAKE) -C ./sources/libft/

$(NAME): $(LIBFT_A) $(OBJS_PATH) $(HEADERS)
	$(CC) -o $@ $(OBJS_PATH) $(LIBFT_A) $(INCLUDE)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) Makefile
	$(CC) -o $@ -c $< $(INCLUDE) $(FLAGS)

clean :
	$(RM) -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: clean fclean all re make_lib