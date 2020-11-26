NAME = lem-in
LIBFT = sources/libft/libft.a

CC = gcc

FLAGS =

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

all: $(LIBFT) $(NAME)

$(LIBFT) : make_lib
	@mkdir -p $(OBJ_DIR)

make_lib:
	@make -C ./sources/libft/

$(NAME): $(OBJS_PATH) $(LIBFT) $(HEADERS)
	$(CC) -o $@ $(OBJS_PATH) $(LIBFT) $(INCLUDE)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) Makefile
	$(CC) -o $@ -c $< $(INCLUDE) $(FLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C ./sources/libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./sources/libft/ fclean

re: fclean all

.PHONY: make_lib clean fclean re