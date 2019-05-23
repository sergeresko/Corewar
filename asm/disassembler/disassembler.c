/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/23 08:52:03 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_args_types_by_codage(unsigned char c, t_com *command) {
	unsigned char	t;

	t = c >> 6;
	command->arg_types[0] = t == IND_CODE ? T_IND : t;
	t = c << 2;
	command->arg_types[1] = t >> 6 == IND_CODE ? T_IND : t;
	t = c << 4;
	command->arg_types[2] = t >> 6 == IND_CODE ? T_IND : t;
}

char	*get_command_name_by_code(int c)
{
	char	commands[16][5] = {
			"live", "ld", "st", "add", "sub", "and", "or", "xor",
			"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};
	c--;
	if (c < 0 || c > 16)
	{
		ft_printf("Command code '%x' is NOT valid\n", c);
		exit(-1);
	}
	return (ft_strdup(commands[c]));
}

void	read_code(char *code, int lenght, int fd)
{
	int 	i;
	char	*com_name;
	t_com	*command;

	i = 4;	// skip last null
	while (i < lenght)
	{
		com_name = get_command_name_by_code(code[i++]);
		command = check_command(com_name);
		if (command->is_codage)
			get_args_types_by_codage(code[i++], command);
//		i = read_args_by_codage(code, i, command);
//		write_args_to_file(fd, command);
		ft_strdel(&com_name);
		ft_memdel((void **)&(command));
	}
}

void	execution_code_processing(int new_file_fd, t_player *player)
{
	char	*code;

	if (!(code = ft_strnew(sizeof(char) * player->size)))
	{
		perror("execution_code_processing_1");
		exit(-1);
	}
	if (read(player->fd, code, player->size) != player->size)
	{
		perror("execution_code_processing_2");
		exit(-1);
	}
	read_code(code, player->size, new_file_fd);
	ft_strdel(&code);
}

void	write_header(int fd, t_player *player)
{
	ft_putstr_fd(".name \"", fd);
	ft_putstr_fd(player->name, fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(".comment \"", fd);
	ft_putstr_fd(player->comment, fd);
	ft_putstr_fd("\"\n\n", fd);
}

void	clean_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		ft_strdel(&(split[i++]));
	free(split);
}

char	*get_filename_from_path(const char *filepath)
{
	int 	i;
	char	*name;
	char	**temp1;
	char	**temp2;

	name = NULL;
	if ((temp1 = ft_strsplit(filepath, '.')))
	{
		i = -1;
		while (temp1[++i])
			if (!temp1[i + 2])
				break ;
		if ((temp2 = ft_strsplit(temp1[i], '/')))
		{
			i = -1;
			while (temp2[++i])
				if (!temp2[i + 1])
					break ;
			name = ft_strjoin(temp2[i], ".s");
			clean_split(temp1);
			clean_split(temp2);
		}
	}
	return (name);
}

int		create_new_file(t_player *player)
{
	int 	fd;
	char	*new_file;

	if (!(new_file = get_filename_from_path(player->filename)))
	{
		perror("create_new_file");
		exit(-1);
	}
	ft_printf("Writing output program to %s\n", new_file);
	fd = open(new_file, O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0744);
	ft_strdel(&new_file);
	return (fd);
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

void	player_initialization(t_player *player, int fd, const char *filename)
{
	ft_bzero((void *)player, sizeof(t_player));
	player->fd = fd;
	player->filename = filename;
}

void	disassemble_processing(int fd, const char *filename)
{
	t_player	player;
	int			new_file_fd;

	player_initialization(&player, fd, filename);
	check_filename(player.filename);
	read_headers(&player);
	ft_printf("Name: %s\n", player.name);
	ft_printf("Comment: %s\n", player.comment);
	ft_printf("Size: %d bytes\n", player.size);

	new_file_fd = create_new_file(&player);
	write_header(new_file_fd, &player);
	execution_code_processing(new_file_fd, &player);
	close(new_file_fd);

	ft_strdel(&(player.name));
	ft_strdel(&(player.comment));
}
