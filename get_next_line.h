#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 42
#endif
typedef struct content_list
{
	char	*buf;
	c_list	next;
}	c_list
typedef struct file_list
{
	c_list	countent;
	int	fd;
	f_list	next;
}	f_list

char	*get_next_line(int fd);
#endif
