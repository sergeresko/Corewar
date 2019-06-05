/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:33:15 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/05 07:58:37 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_command_line(t_asm *asm_struct)
{
	t_com	*new_command;

	check_command_arguments(asm_struct->command);
	if (asm_struct->command->is_codage)
		asm_struct->command->codage = make_codage(asm_struct->command);
	asm_struct->command->length = command_length(asm_struct->command);
	asm_struct->command->index = g_index;
	g_index += asm_struct->command->length;
	new_command = ft_memalloc(sizeof(t_com));
	push_command_front(&(asm_struct->commands),
		ft_memcpy(new_command, asm_struct->command, sizeof(t_com)));
	ft_memdel((void **)(&(asm_struct->command)));
}

char	make_codage(t_com *command)
{
	int		count;
	char	result;

	count = 0;
	result = 0;
	while (count < 3)
	{
		if (command->arg_types[count] == T_REG)
			result = result | (char)REG_CODE;
		else if (command->arg_types[count] == T_DIR)
			result = result | (char)DIR_CODE;
		else if (command->arg_types[count] == T_IND)
			result = result | (char)IND_CODE;
		result = result << 2;
		count++;
	}
	return (result);
}

int		command_length(t_com *command)
{
	int		count;
	int		result;

	count = 0;
	result = 1;
	while (count < 3)
	{
		if (command->arg_types[count] == T_REG)
			result += 1;
		else if (command->arg_types[count] == T_DIR)
			result += command->label_size;
		else if (command->arg_types[count] == T_IND)
			result += 2;
		count++;
	}
	if (command->is_codage)
		result += 1;
	return (result);
}

void	write_arg(t_com *com, int a_n, t_arg_type a_t, int arg)
{
	com->arg_types[a_n] = a_t;
	if (a_t == T_REG)
		com->arguments[a_n] = (char)arg;
	else if (a_t == T_DIR && com->label_size == LABEL_SIZE_2)
		com->arguments[a_n] = (short)arg;
	else
		com->arguments[a_n] = arg;
}

void	write_l_a(t_com *com, int a_n, t_arg_type a_t, char **l)
{
	com->arg_types[a_n] = a_t;
	com->arg_labels[a_n] = *l;
}
