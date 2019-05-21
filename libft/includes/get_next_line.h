/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:54:08 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/04 00:14:24 by zaliskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_fdlist
{
	int				fd;
	char			buf[BUFF_SIZE + 1];
	int				i;
	int				r;
	struct s_fdlist	*next;
}					t_fdlist;

int					get_next_line(const int fd, char **line);
t_fdlist			*find_fd(t_fdlist **head, int fd);
int					write_line(char **line, t_fdlist *node, int is_read);
int					spacing(char **line, int ex_space);
void				node_delete(t_fdlist **head, int fd);

#endif
