/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:35:28 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:37:22 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 	check_proper_ending(const char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			++i;
		else if (line[i] == '#')
		{
			while (line[i] != '\0')
				++i;
		}
		else if (line[i] == SEPARATOR_CHAR || line[i] == '\n')
			return (++i);
		else
		{
			g_error_mode = TRUE;
			return (i);
		}
	}
	return (i);
}

void	cook_champion(t_asm *asm_struct)
{
	int 	i;
	int 	length;

	length = g_index * 2;
	asm_struct->header.size = (unsigned int)g_index;
	if ((asm_struct->champion = ft_strnew(sizeof(char) * length)))
	{
		i = 0;
		ft_memset(asm_struct->champion, '0', (size_t)length);
		cook_command(asm_struct->commands, i, asm_struct);
	}
	else
		perror("");
}

void	cook_command_2(t_com *command, t_asm *asm_struct, int current_index)
{
	if (command->arg_types[0])
		current_index = !command->arg_labels[0]
						? cook_arg(command, 0, current_index, asm_struct)
						: cook_l_arg(command, 0, current_index, asm_struct);
	if (command->arg_types[1])
		current_index = !command->arg_labels[1]
						? cook_arg(command, 1, current_index, asm_struct)
						: cook_l_arg(command, 1, current_index, asm_struct);
	if (command->arg_types[2])
		!command->arg_labels[2]
		? cook_arg(command, 2, current_index, asm_struct)
		: cook_l_arg(command, 2, current_index, asm_struct);
}

void	cook_command(t_com *command, int i, t_asm *asm_struct)
{
	char	*temp;
	int 	current_index;

	if (command->next)
		cook_command(command->next, i + command->length, asm_struct);
	current_index = (g_index - i - command->length) * 2;
	temp = byte_in_hex((unsigned char)command->code);
	ft_strncpy(&(asm_struct->champion[current_index]), temp, 2);
	current_index += 2;
	ft_strdel(&temp);
	if (command->is_codage)
	{
		temp = byte_in_hex((unsigned char)command->codage);
		ft_strncpy(&(asm_struct->champion[current_index]), temp, 2);
		current_index += 2;
		ft_strdel(&temp);
	}
	cook_command_2(command, asm_struct, current_index);
}


int		cook_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;

	if (com->arg_types[a_n] == T_REG)
	{
		temp = byte_in_hex((unsigned char)com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, 2);
		index += 2;
	}
	else if (com->arg_types[a_n] == T_DIR)
	{
		if (com->label_size == 2)
			temp = short_in_hex((unsigned short)com->arguments[a_n]);
		else
			temp = integer_in_hex(com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, com->label_size == 2 ? 4 : 8);
		index += com->label_size == 2 ? 4 : 8;
	}
	else if (com->arg_types[a_n] == T_IND)
	{
		temp = short_in_hex((unsigned short)com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, 4);
		index += 4;
	}
	ft_strdel(&temp);
	return (index);
}

int 	cook_l_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;
	int 	delta;
	int 	label_index;

	if ((label_index = get_label_index(asm_str->labels, com->arg_labels[a_n])) != -1)
	{
		if (com->arg_types[a_n] == T_DIR)
		{
//			ft_printf("Direct %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - com->index) >= 0)
				temp = com->label_size == 2
					   ? short_in_hex(delta)
					   : integer_in_hex(delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]), temp, com->label_size == 2 ? 4 : 8);
			index += com->label_size == 2 ? 4 : 8;
			ft_strdel(&temp);
			return index;
		}
		else if (com->arg_types[a_n] == T_IND)
		{
//			ft_printf("Indirect %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - com->index) >= 0)
				temp = short_in_hex(delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]), temp, 4);
			index += 4;
			ft_strdel(&temp);
			return index;
		}
		return (index + 1 + (int)ft_strlen(com->arg_labels[a_n]));
	}
	ft_printf("No such label %s while attempting to dereference token %s \"%c%s\"\n",
			  com->arg_labels[a_n],
			  com->arg_types[a_n] == T_DIR ? "DIRECT_LABEL" : "INDIRECT_LABEL",
			  com->arg_types[a_n] == T_DIR ? '%' : ':', com->arg_labels[a_n]);
	exit(-1);
}
