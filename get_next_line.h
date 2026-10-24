#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
typedef struct content_list
{
	char				*buf;
	struct content_list	*next;
}	c_list;

typedef struct file_list
{
	c_list				*content;
	int					fd;
	struct file_list	*next;
}	f_list;

char    *free_all(c_list **content_list);
char	*get_next_line(int fd);
#endif
