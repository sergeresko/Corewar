/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 19:02:40 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	disassemble_processing(int fd, const char *filename)
{
	t_player	player;
	int			new_file_fd;

	player_init(&player, fd, filename);
	check_filename(player.filename);
	read_header(&player);
	new_file_fd = create_new_file(&player);
	write_header(new_file_fd, &player);
	exec_code_proc(new_file_fd, &player);
	ft_printf("Writing output program to %s\n", player.new_file);
	close(new_file_fd);
	ft_strdel(&(player.name));
	ft_strdel(&(player.comment));
	ft_strdel(&(player.new_file));
}

void	check_filename(const char *filename)
{
	char *const	extension = ft_strrchr(filename, '.');

	if (extension == NULL || extension == filename
			|| extension[-1] == '/' || !ft_strequ(extension, ".cor"))
	{
		ft_printf("Not a valid .cor file '%s'\n", filename);
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
		ft_putendl("Code procesing error!");
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
