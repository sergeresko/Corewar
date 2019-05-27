/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_and_writers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:48:23 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:05:20 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_args_types(t_com *command)
{
	if (ft_strequ(command->name, "live"))
		command->arg_types[0] = T_DIR;
	else if (ft_strequ(command->name, "zjmp"))
		command->arg_types[0] = T_DIR;
	else if (ft_strequ(command->name, "fork"))
		command->arg_types[0] = T_DIR;
	else if (ft_strequ(command->name, "lfork"))
		command->arg_types[0] = T_DIR;
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

void	write_args_to_file(int fd, t_com *command)
{
	int		i;
	char	*value;

	i = 0;
	ft_putstr_fd(command->name, fd);
	while (i < 3 && command->arg_types[i])
	{
		ft_putchar_fd(' ', fd);
		value = ft_itoa(command->arguments[i]);
		if (command->arg_types[i] == T_REG)
			ft_putchar_fd('r', fd);
		else if (command->arg_types[i] == T_DIR)
			ft_putchar_fd('%', fd);
		ft_putstr_fd(value, fd);
		if (++i < 3 && command->arg_types[i])
			ft_putchar_fd(SEPARATOR_CHAR, fd);
		else
			ft_putchar_fd('\n', fd);
		ft_strdel(&value);
	}
}
