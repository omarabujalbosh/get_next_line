#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 42
#endif
typedef struct content_list
{
	char				*buf;
	struct content_list	*next;
}	c_list;

void	ft_lstadd_back(c_list **lst, c_list *new);
c_list	*ft_lstnew(void *content);
char	*free_all(c_list **content);
int		line_len(c_list **content);
int		remainder_len(char *buf);
char *get_remainder(c_list **cuntent, c_list *current, char **line);
char	*merge_line(c_list **content);
char	*readline(int fd, c_list **content);
char	*get_next_line(int fd);
int		has_newline(c_list *content);
char	*append_remainder(char *dst, char *src, int len);

#endif
