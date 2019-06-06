/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_getters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:40:10 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 19:07:32 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	player_init(t_player *pl, int fd, const char *file)
{
	ft_bzero((void *)pl, sizeof(t_player));
	pl->fd = fd;
	pl->filename = file;
}

char	*get_filename_from_path(const char *filepath)
{
	char	*temp;
	char	*name;

	if (!(temp = ft_strsub(filepath, 0, ft_strlen(filepath) - 4)))
	{
		perror("get_filename_from_path");
		exit(-1);
	}
	name = ft_strjoin(temp, ".s");
	ft_strdel(&temp);
	return (name);
}

char	*get_command_name_by_code(int c)
{
	static char	commands[16][5] = {
		"live", "ld", "st", "add", "sub", "and", "or", "xor",
		"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

	if (c < 1 || c > 16)
	{
		ft_printf("Command code '%x' is NOT valid\n", c);
		exit(-1);
	}
	return (ft_strdup(commands[c - 1]));
}

void	get_args_types_by_codage(unsigned char c, t_com *command)
{
	unsigned char	t;

	t = c >> 6;
	command->arg_types[0] = (t == IND_CODE) ? T_IND : t;
	t = c << 2;
	t >>= 6;
	command->arg_types[1] = (t == IND_CODE) ? T_IND : t;
	t = c << 4;
	t >>= 6;
	command->arg_types[2] = (t == IND_CODE) ? T_IND : t;
	if (!check_arg_1(command->name, 0, command->arg_types[0])
	|| !check_arg_1(command->name, 1, command->arg_types[1])
	|| !check_arg_1(command->name, 2, command->arg_types[2]))
	{
		ft_printf("Wrong arguments for '%s'\n", command->name);
		exit(-1);
	}
}

int		create_new_file(t_player *player)
{
	int		fd;

	if (!(player->new_file = get_filename_from_path(player->filename)))
	{
		perror("create_new_file");
		exit(-1);
	}
	fd = open(player->new_file, O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0744);
	return (fd);
}
