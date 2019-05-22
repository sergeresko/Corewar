/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/22 23:27:38 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_filename(const char *filename)
{
	int		i;
	char	**splitname;

	if (!(splitname = ft_strsplit(filename, '.')))
	{
		perror("check_filename");
		exit(-1);
	}
	i = 0;
	while (splitname[i])
	{
		if (!splitname[i + 1] && !ft_strequ(splitname[i], "cor"))
		{
			ft_printf("\"%s\" is NOT a correct filename!\n", filename);
			exit(-1);
		}
		i++;
	}
	i = 0;
	while (splitname[i])
		ft_strdel(&(splitname[i++]));
	free(splitname);
}

void	player_initialization(t_player *player, int fd, const char *filename)
{
	ft_bzero((void *)player, sizeof(t_player));
	player->fd = fd;
	player->filename = filename;
}

void	disassemble_processing(int fd, const char *filename)
{
	ft_printf("Disassemble processing!\n");

	t_player	player;

	player_initialization(&player, fd, filename);
	check_filename(player.filename);
	read_headers(&player);
	ft_printf("Name: %s\n", player.name);
	ft_printf("Comment: %s\n", player.comment);
	ft_printf("Size: %d bytes\n", player.size);


	ft_strdel(&(player.name));
	ft_strdel(&(player.comment));
}
