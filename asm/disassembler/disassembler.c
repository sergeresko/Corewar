/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 19:06:33 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	disassemble_processing(int fd, const char *filename)
{
	t_player	player;
	int			new_file_fd;

	player_init(&player, fd, filename);
	check_filename(player.filename);
	read_headers(&player);
	new_file_fd = create_new_file(&player);
	write_header(new_file_fd, &player);
	exec_code_proc(new_file_fd, &player);
	close(new_file_fd);
	ft_strdel(&(player.name));
	ft_strdel(&(player.comment));
}

void	check_filename(const char *filename)
{
	int		len;

	len = (int)ft_strlen(filename);
	if (len <= 4 || filename[len - 1] != 'r' || filename[len - 2] != 'o'
	|| filename[len - 3] != 'c' || filename[len - 4] != '.')
	{
		ft_putendl("Not a valid .cor file");
		exit(-1);
	}
}

void	exec_code_proc(int new_file_fd, t_player *player)
{
	int		test;
	char	*code;

	if (!(code = ft_strnew(sizeof(char) * player->size)))
	{
		perror("execution_code_processing_1");
		exit(-1);
	}
	if ((test = read(player->fd, code, player->size)) != player->size)
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
