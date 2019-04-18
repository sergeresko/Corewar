/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/08 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	dump_output(t_asm *asm_struct)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", g_index);
	ft_printf("Name : \"%s\"\n", asm_struct->header.name);
	ft_printf("Comment : \"%s\"\n\n", asm_struct->header.description);
	rush_through_commands(asm_struct->commands, 0, asm_struct);
}

void	rush_through_commands(t_com *command, int index, t_asm *asm_struct)
{
	char	*temp;
	char	*label_name;
	int 	current_index;

	if (command->next)
		rush_through_commands(command->next, index + command->length, asm_struct);
	current_index = g_index - index - command->length;
	if ((label_name = get_label_name(asm_struct->labels, current_index)))
	{
		temp = ft_itoa(current_index);
		print_in_length(11, &temp);
		ft_printf(":    %s:\n", label_name);
	}
	print_command_line(command, current_index);
//	print_additional_command_line(command, 1);
}

void	print_command_line(t_com *command, int index)
{
	int 	i;
	char	*temp;

	i = -1;
	temp = ft_itoa(index);
	print_in_length(5, &temp);
	ft_putchar('(');
	temp = ft_itoa(command->length);
	print_in_length(3, &temp);
	ft_putstr(") :        ");
	print_in_length(10, &(command->name));
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
			temp = command->arg_labels[i] ? ft_strjoin(":", command->arg_labels[i]) : ft_itoa(command->arguments[i]);
			ft_putchar('%');
			print_in_length(17, &temp);
		}
		else
		{
			temp = command->arg_labels[i] ? ft_strjoin(":", command->arg_labels[i]) : ft_itoa(command->arguments[i]);
			print_in_length(18, &temp);
		}
	}
	ft_putchar('\n');
}

void	print_additional_command_line(t_com *command, int line)
{
	int 	i;
	char	*temp;

	i = -1;
	ft_printf("                    ");
	temp = ft_itoa(command->code);
	print_in_length(4, &temp);
	if (command->is_codage)
	{
		temp = ft_itoa(command->codage);
		print_in_length(6, &temp);
	}
//	while (++i < 3)
//	{
//		if (!command->arg_labels[i])
//			temp = ft_itoa(command->arguments[i]);
//		else
//		{
//
//		}
//		print_in_length(18, &temp);
//	}
	ft_putchar('\n');
}

void	print_in_length(int length, char **str)
{
	int i;
	int len;

	if (str && *str)
	{
		i = 0;
		len = (int) ft_strlen(*str);
		while (i < length)
		{
			if (i < len)
			{
				ft_printf("%c", (*str)[i++]);
				continue;
			}
			ft_putchar(' ');
			i++;
		}
		ft_strdel(str);
		return ;
	}
	perror("Print in length");
	exit(-1);
}
