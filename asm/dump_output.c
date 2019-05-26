/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:26:19 by vlvereta         ###   ########.fr       */
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
	print_additional_command_line(command, 1, asm_struct);
	print_additional_command_line(command, 2, asm_struct);
	ft_putchar('\n');
}

void	print_additional_command_line(t_com *command, int line, t_asm *ast_struct)
{
	int 	i;
	char	*temp;
	int 	label_index;
	int		label_arg;

	i = -1;
	ft_printf("                    ");
	temp = ft_itoa(command->code);
	print_in_length(4, &temp);
	temp = command->is_codage ? ft_itoa(command->codage) : NULL;
	print_in_length(6, &temp);
	while (++i < 3)
	{
		if (command->arg_labels[i])
		{
			label_index = get_label_index(ast_struct->labels, command->arg_labels[i]);
			label_arg = label_index - command->index;
		}
		else
			label_arg = command->arguments[i];
		if (command->arg_types[i] == T_REG)
		{
			temp = ft_itoa((unsigned char)label_arg);
			print_in_length(18, &temp);
			continue ;
		}
		else if (command->arg_types[i] == T_IND)
		{
			if (line == 2)
			{
				temp = ft_itoa(label_arg);
				print_in_length(18, &temp);
				continue ;
			}
			print_by_bytes(label_arg, 2);
			ft_putstr("          ");
		}
		else if (command->arg_types[i] == T_DIR)
		{
			if (line == 2)
			{
				temp = ft_itoa(label_arg);
				print_in_length(18, &temp);
				continue ;
			}
			print_by_bytes(label_arg, command->label_size);
			if (command->label_size == 2)
				ft_putstr("          ");
			else
				ft_putstr("  ");
		}
	}
	ft_putchar('\n');
}

void	print_by_bytes(int arg, int bytes)
{
	int 			i;
	char 			*t;
	unsigned char	temp;

	i = 0;
	while (i < bytes)
	{
		temp = arg >> (bytes - ++i) * BYTE;
		t = ft_itoa(temp);
		print_in_length(4, &t);
	}
}

void	print_in_length(int length, char **str)
{
	int i;
	int len;

	if (str)
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
