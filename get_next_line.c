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

int	is_new_line(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstadd_back(c_list **lst, c_list *new)
{
	c_list	*pre;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	pre = *lst;
	while (pre->next)
		pre = pre->next;
	pre->next = new;
}

c_list	*ft_lstnew(void *content)
{
	c_list	*newl;

	newl = malloc(sizeof(c_list));
	if (!newl)
		return (NULL);
	newl -> buf = content;
	newl -> next = NULL;
	return (newl);
}
char *free_all(c_list **cuntent)
{
	c_list	*tmp;

	while (*cuntent)
	{
		tmp = (*cuntent)->next;
		if ((*cuntent)-> buf)
			free((*cuntent)->buf);
		free(*cuntent);
		*cuntent = tmp;
	}
	return (NULL);
}

int	line_len(c_list **cuntent)
{
	c_list	*current;
	int	i;
	int	j;

	i = 0;
	current = *cuntent;
	while (current->next)
	{
		j = 0;
		while (current->buf[j++])
			i++;
		current = current->next;
	}
	j = 0;
	while(current->buf[j] && current->buf[j] != '\n')
		i++;
	if (current->buf[j] == '\n')
		i++;
	return (i);
}
int	remainder_len(char *buf)
{
	int	flag;
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!buf)
		return (0);
	flag = 1;
	while (buf[i])
	{
		if (buf[i] == '\n')
			flag = 1;
			
		if (flag)
			len++;
		i++;
	}
	return (len);
}
char *get_remainder(c_list **cuntent, c_list *current, char **line)
{
	char	*new;
	int	newlen;
	int	i;
	int	j;

	i = 0;
	j = 0;
	newlen = remainder_len(current->buf);
	new = malloc(newlen);
	if (!new)
	{
		free(line);
		return (NULL);
	}
	while (current->buf[i] && current->buf[i] != '\n')
	{
		*line[i] = current->buf[i];
		i++;
	}
	while (current->buf[i] && newlen--)
		new[j++] = current->buf[++i];
	free_all(cuntent);
	ft_lstadd_back(cuntent, ft_lstnew(new));
	return (*line);
}

char	*merge_line(c_list **cuntent)
{
	int	len;
	char	*line;
	int	i;
	int	j;
	c_list	*current;

	current = *cuntent;
	len = line_len(cuntent);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (current->next)
	{
		j = 0;
		while (current->buf[j])
		{
			line[i] = current->buf[j];
			i++;
			j++;
		}
		current = current->next;
	}
	line  = get_remainder(cuntent, current, &line);
	line[i] = '\0';
	return (line);
}

char	*readline(int fd, c_list **cuntent)
{
	char	*buf;
	size_t	n;
	c_list	*current;

	current = *cuntent;
	if (*cuntent && (*cuntent)->next)
	while (current->next)
	  current = current->next;
	while (!is_new_line((*cuntent)->buf))
	{
	n = read(fd, buf, BUFFER_SIZE);
	if (n < 0)
		return (free_all(cuntent));
	else if (n == 0 || n < BUFFER_SIZE)
		return (merge_line(cuntent));
	else
		ft_lstadd_back(cuntent, ft_lstnew(buf));
	current = current->next;
	}
	return (merge_line(cuntent));
}

char	*get_next_line(int fd)
{
	static c_list	*cuntent;
	
	if (fd < 0 && read(fd, NULL, 0) < 0)
		return (NULL);
	return(readline(fd, &cuntent));
}
