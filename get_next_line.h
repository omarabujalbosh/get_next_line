#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct content_list
{
	char				*buf;
	struct content_list	*next;
}	c_list;

int		is_new_line(char *buf);
void	ft_lstadd_back(c_list **lst, c_list *new);
c_list	*ft_lstnew(void *content);
char	*free_all(c_list **cuntent);
int		line_len(c_list **cuntent);
int		remainder_len(char *buf);
char	*get_remainder(c_list **cuntent, c_list *current,
			char **line);
char	*merge_line(c_list **cuntent);
char	*get_next_line(int fd);
char	*readline(int fd, c_list **cuntent);
#endif
