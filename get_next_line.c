/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-jal <oabu-jal@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:05:08 by oabu-jal          #+#    #+#             */
/*   Updated: 2026/10/24 17:27:02 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

c_list	*ft_lstnew(void *content)
{
	c_list	*newl;

	newl = malloc(sizeof(c_list));
	if (!newl)
		return (NULL);
	newl->buf = content;
	newl->next = NULL;
	return (newl);
}

void	ft_lstadd_back_cuntent(c_list **lst, c_list *new)
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

int	is_break_line(c_list *current, int is_len)
{
	int	i;
	int	len;

	len = 0;
	while (current)
	{
		i = 0;
		while (current->buf[i])
		{
			if (current->buf[i] == '\n')
			{
				if (is_len)
					return (len + 1);
				return (1);
			}
			i++;
			len++;
		}
		current = current->next;
	}
	if (is_len)
		return (len);
	return (0);
}

static char	*make_line(c_list *current, int len)
{
	char	*line;
	int		i;
	int		j;

	line = malloc((size_t)len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (current && i < len)
	{
		j = 0;
		while (current->buf[j] && i < len)
			line[i++] = current->buf[j++];
		current = current->next;
	}
	line[i] = '\0';
	return (line);
}

static void	free_nodes(c_list *node)
{
	c_list	*next;

	while (node)
	{
		next = node->next;
		free(node->buf);
		free(node);
		node = next;
	}
}

static int	list_len(c_list *current)
{
	int	len;
	int	i;

	len = 0;
	while (current)
	{
		i = 0;
		while (current->buf[i])
		{
			len++;
			i++;
		}
		current = current->next;
	}
	return (len);
}

static void	copy_rest(c_list *current, char *rest, int consumed)
{
	int	i;
	int	j;

	i = 0;
	while (current)
	{
		j = 0;
		while (current->buf[j])
		{
			if (i >= consumed)
				rest[i - consumed] = current->buf[j];
			i++;
			j++;
		}
		current = current->next;
	}
}

static int	save_rest(c_list **list, int consumed)
{
	char	*rest;
	c_list	*node;
	int		total;

	total = list_len(*list);
	if (total <= consumed)
	{
		free_nodes(*list);
		*list = NULL;
		return (1);
	}
	rest = malloc((size_t)(total - consumed) + 1);
	if (!rest)
		return (0);
	copy_rest(*list, rest, consumed);
	rest[total - consumed] = '\0';
	node = ft_lstnew(rest);
	if (!node)
	{
		free(rest);
		return (0);
	}
	free_nodes(*list);
	*list = node;
	return (1);
}

char	*join_buf(c_list **content_list)
{
	char	*line;
	int		len;

	if (!content_list || !*content_list)
		return (NULL);
	len = is_break_line(*content_list, 1);
	line = make_line(*content_list, len);
	if (!line)
		return (NULL);
	if (!save_rest(content_list, len))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*free_all(c_list **content_list)
{
	if (content_list)
	{
		free_nodes(*content_list);
		*content_list = NULL;
	}
	return (NULL);
}

int	read_buf(int fd, c_list **content)
{
	int		n;
	c_list	*node;
	char	*buf;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buf);
		return (n);
	}
	buf[n] = '\0';
	node = ft_lstnew(buf);
	if (!node)
	{
		free(buf);
		return (-1);
	}
	ft_lstadd_back_cuntent(content, node);
	return (n);
}

char	*read_line(f_list *current_file, int fd)
{
	int	n;

	if (!current_file)
		return (NULL);
	while (!is_break_line(current_file->content, 0))
	{
		n = read_buf(fd, &current_file->content);
		if (n < 0)
			return (free_all(&current_file->content));
		if (n == 0)
			break ;
	}
	if (!current_file->content)
		return (NULL);
	return (join_buf(&current_file->content));
}

void	add_file(int fd, f_list **list)
{
	f_list	*node;
	f_list	*pre;

	node = malloc(sizeof(f_list));
	if (!node)
		return ;
	node->fd = fd;
	node->content = NULL;
	node->next = NULL;
	if (!*list)
	{
		*list = node;
		return ;
	}
	pre = *list;
	while (pre->next)
		pre = pre->next;
	pre->next = node;
}

char	*get_next_line(int fd)
{
	static f_list	*list;
	f_list			*current;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	current = list;
	while (current && current->fd != fd)
		current = current->next;
	if (!current)
	{
		add_file(fd, &list);
		current = list;
		while (current && current->fd != fd)
			current = current->next;
	}
	if (!current)
		return (NULL);
	return (read_line(current, fd));
}

