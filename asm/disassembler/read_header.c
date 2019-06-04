/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:01:54 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 23:42:07 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_header(t_player *player)
{
	char	*header;

	if (!player || !(header = ft_strnew(sizeof(char) * 2192)))
	{
		perror("read_headers_1");
		exit(-1);
	}
	ft_bzero(header, 2192);
	if (read(player->fd, header, 2192) != 2192)
	{
		perror("read_headers_2");
		exit(-1);
	}
	check_magic(header, player);
	player->name = read_player_name(header);
	is_no_null_error(header, 132);
	if ((player->size = parse_int(&(header[136]))) < 0)
	{
		ft_printf("Champion's size is negative: %d\n", player->size);
		exit(-1);
	}
	player->comment = read_player_comment(header);
	is_no_null_error(header, 2188);
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

void	is_no_null_error(char *str, int i)
{
	if (parse_int(&(str[i])))
	{
		ft_printf("No null at %d\n", i);
		exit(-1);
	}
}
