/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:26:24 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:30:41 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_command_line(t_com *command, int index)
{
	char	*temp;

	temp = ft_itoa(index);
	print_in_length(5, &temp);
	ft_putchar('(');
	temp = ft_itoa(command->length);
	print_in_length(3, &temp);
	ft_putstr(") :        ");
	print_in_length(10, &(command->name));
	print_command_line_loop(command, -1, temp);
	ft_putchar('\n');
}

void	print_command_line_loop(t_com *command, int i, char *temp)
{
	while (++i < 3)
	{
		if (command->arg_types[i] == T_REG)
		{
			temp = ft_itoa(command->arguments[i]);
			ft_putchar('r');
			print_in_length(17, &temp);
		}
		else if (command->arg_types[i] == T_DIR)
		{
			temp = command->arg_labels[i]
					? ft_strjoin(":", command->arg_labels[i])
					: ft_itoa(command->arguments[i]);
			ft_putchar('%');
			print_in_length(17, &temp);
		}
		else if (command->arg_types[i] == T_IND)
		{
			temp = command->arg_labels[i]
					? ft_strjoin(":", command->arg_labels[i])
					: ft_itoa(command->arguments[i]);
			print_in_length(18, &temp);
		}
	}
}
