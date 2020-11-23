#ifndef IO_H
# define IO_H

# define BUFF_SIZE 512

typedef struct			s_fd_list
{
	int					fd;
	char				*line;
	struct s_fd_list	*next;
}						t_fd_list;

int						get_next_line(int fd, char **line);
void					ft_putendl(const char *s);

#endif
