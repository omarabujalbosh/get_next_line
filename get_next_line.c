/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-jal <oabu-jal@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:05:08 by oabu-jal          #+#    #+#             */
/*   Updated: 2026/10/22 12:55:09 by oabu-jal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

c_list	*ft_lstnew(void *content)
{
	t_list	*newl;

	newl = malloc(sizeof(t_list));
	if (!newl)
		return (NULL);
	newl -> content = content;
	newl -> next = NULL;
	return (newl);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pre;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	pre = ft_lstlast(*lst);
	pre->next = new;
}
void	read_buf(int fd, c_list cuntent)
{
	int	n;
	c_list	node;
	char	*buf;

	n = read(fd, buf,  BUFFER_SIZE);
	if (n > 0)
		ft_lstadd_back(cuntent, node = ft_lstlast(buf));
	else if (n == 0)
		return ;
	else if (n < 0)

}

char	*read_line(f_list current_file)
{
	char	*line;
	char	*buf;

	if (!current_file->cuntent)
		read_buf(fd, cuntent_file->cuntent);
}

char	*get_next_line(int fd)
{
	static f_list	*list;
	f_list	*current;
	char	*line;

	current = list;
	if (fd < 0)
		return (NULL);
	if (!list)
		ft_lstadd_back(&list, add_file(fd));
	while(current->next)
	{
		if (current->fd == fd)
			line = read_line(current);
		current = current->next;

	}

}
