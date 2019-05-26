/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 17:48:56 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	disassemble_processing(int fd, const char *filename)
{
	t_player	player;
	int			new_file_fd;

	player_initialization(&player, fd, filename);
	check_filename(player.filename);
	read_headers(&player);
	new_file_fd = create_new_file(&player);
	write_header(new_file_fd, &player);
	execution_code_processing(new_file_fd, &player);
	close(new_file_fd);
	ft_strdel(&(player.name));
	ft_strdel(&(player.comment));
}

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
	clean_split(splitname);
}

void	execution_code_processing(int new_file_fd, t_player *player)
{
	int 	test;
	char	*code;

	if (!(code = ft_strnew(sizeof(char) * player->size)))
	{
		perror("execution_code_processing_1");
		exit(-1);
	}
	if (read(player->fd, code, player->size) != player->size)
	{
		ft_printf("%d != %d\n", test, player->size);
		perror("execution_code_processing_2");
		exit(-1);
	}
	read_code(code, player->size, new_file_fd);
	ft_strdel(&code);
}

void	clean_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		ft_strdel(&(split[i++]));
	free(split);
}
