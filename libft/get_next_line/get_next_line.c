/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:53:53 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/21 17:16:45 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	main function. Checks errors and performs functionality
*/

int			get_next_line(const int fd, char **line)
{
	t_fdlist		*node;
	static t_fdlist	*head;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	if (!(node = find_fd(&head, fd)))
		return (-1);
	if (!node->i && !node->r)
	{
		node_delete(&head, fd);
		return (0);
	}
	return (write_line(line, node, 0));
}

/*
**	to find fd's node or creates new
*/

t_fdlist	*find_fd(t_fdlist **head, int fd)
{
	t_fdlist	*new;
	t_fdlist	*temp;

	if ((temp = *head))
	{
		while (temp)
		{
			if (temp->fd == fd)
				return (temp);
			temp = temp->next;
		}
	}
	if ((new = (t_fdlist *)malloc(sizeof(t_fdlist))))
	{
		ft_bzero(new, sizeof(t_fdlist));
		new->fd = fd;
		new->next = *head;
		if ((new->r = read(fd, new->buf, BUFF_SIZE)) == -1)
			ft_memdel((void **)(&new));
		else
			*head = new;
	}
	return (new);
}

/*
**	HEART of the function!
**	to write line from buffer and returns state
*/

int			write_line(char **line, t_fdlist *node, int is_read)
{
	int		j;

	if (node->i == node->r)
	{
		if ((node->r = read(node->fd, node->buf, BUFF_SIZE)) == -1)
			return (-1);
		node->buf[node->r] = '\0';
		node->i = 0;
		if (node->r == 0 && ft_strlen(*line) > 0
		&& ft_get_substr_index(*line, "\n") == -1)
			return (5);
		return (!(node->r) ? is_read : write_line(line, node, is_read));
	}
	j = node->i;
	while (j < node->r && node->buf[j] != '\n')
		j++;
	if ((j = spacing(line, j)) == -1)
		return (-1);
	while (node->i < node->r && node->buf[node->i] != '\n')
		(*line)[j++] = node->buf[(node->i)++];
	if (node->buf[(node->i)++] == '\n')
		return (1);
	(node->i)--;
	return (write_line(line, node, 1));
}

/*
**	to enlarge line's space and returns index to continue writing
*/

int			spacing(char **line, int ex_space)
{
	int		len;
	char	*temp;

	if (*line)
	{
		len = ft_strlen(*line);
		if ((temp = ft_strnew(len + ex_space)))
			temp = ft_strncpy(temp, *line, len);
		ft_strdel(line);
		*line = temp;
		return (len);
	}
	else if ((*line = ft_strnew(ex_space)))
		return (0);
	return (-1);
}

/*
**	to delete fd's node and points new head if needed
*/

void		node_delete(t_fdlist **head, int fd)
{
	t_fdlist	*del;
	t_fdlist	*temp;

	if ((temp = *head))
	{
		if (temp->fd == fd)
		{
			*head = temp->next;
			ft_memdel((void **)(&temp));
		}
		else
		{
			while (temp->next && temp->next->fd != fd)
				temp = temp->next;
			del = temp->next;
			temp->next = temp->next->next;
			ft_memdel((void **)(&del));
		}
	}
}
