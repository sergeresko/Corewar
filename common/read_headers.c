/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_headers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:01:54 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/23 14:11:56 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

void	read_headers(t_player *players)
{
	char	*header;

	if (!(header = ft_strnew(sizeof(char) * 2188)))
	{
		perror("read_headers_1");
		exit(-1);
	}
	while (players)
	{
		ft_bzero(header, 2188);
		if (read(players->fd, header, 2188) != 2188)
		{
			perror("read_headers_2");
			exit(-1);
		}
		check_magic(header, players);
		players->name = read_player_name(header);
		is_no_null_error(header, 132);
		if ((players->size = parse_int(&(header[136]))) > CHAMP_MAX_SIZE)
		{
			ft_printf("Size field in \"%s\" header is too large\n");
			exit(-1);
		}
		players->comment = read_player_comment(header);
		is_no_null_error(header, 2184);
		players = players->next;
	}
	ft_strdel(&header);
}

void	check_magic(char *header, t_player *player)
{
	if (parse_int(header) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("No magic in \"%s\"\n", player->filename);
		exit(-1);
	}
}

char	*read_player_name(const char *header)
{
	int		i;
	char	*name;

	if (!(name = ft_strnew(sizeof(char) * NAME_LENGTH)))
	{
		perror("read_player_name");
		exit(-1);
	}
	i = 0;
	header += 4;
	while (header[i] && i < NAME_LENGTH)
	{
		name[i] = (char)header[i];
		i++;
	}
	return (name);
}

char	*read_player_comment(const char *header)
{
	int		i;
	char	*comment;

	if (!(comment = ft_strnew(sizeof(char) * DESC_LENGTH)))
	{
		perror("read_player_comment");
		exit(-1);
	}
	i = 0;
	header += 140;
	while (header[i] && i < DESC_LENGTH)
	{
		comment[i] = (char)header[i];
		i++;
	}
	return (comment);
}
