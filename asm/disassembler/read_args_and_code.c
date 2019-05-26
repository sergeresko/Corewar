/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_and_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:37:05 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 17:42:47 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 	read_args_by_types(char *code, int i, t_com *command)
{
	int		j;

	j = 0;
	while (j < 3)
	{
		if (command->arg_types[j] == T_REG)
			i = read_register_by_type(code, i, command, j);
		else if (command->arg_types[j] == T_DIR)
			i = read_direct_by_type(code, i, command, j);
		else if (command->arg_types[j] == T_IND)
			i = read_indirect_by_type(code, i, command, j);
		j++;
	}
	return (i);
}

int 	read_register_by_type(const char *code, int i, t_com *command, int arg_num)
{
	command->arguments[arg_num] = code[i++];
	return (i);
}

int 	read_direct_by_type(const char *code, int i, t_com *command, int arg_num)
{
	int 	j;
	int		direct;

	j = 0;
	direct = 0;
	while (j < command->label_size)
	{
		direct <<= 8;
		direct |= (unsigned char)code[i++];
		j++;
	}
	if (command->label_size == LABEL_SIZE_2)
		command->arguments[arg_num] = (short)direct;
	else if (command->label_size == LABEL_SIZE_4)
		command->arguments[arg_num] = direct;
	return (i);
}

int 	read_indirect_by_type(const char *code, int i, t_com *command, int arg_num)
{
	short	indirect;

	indirect = 0;
	indirect |= (unsigned char)code[i++];
	indirect <<= 8;
	indirect |= (unsigned char)code[i++];
	command->arguments[arg_num] = indirect;
	return (i);
}

void	read_code(char *code, int length, int fd)
{
	int 	i;
	char	*com_name;
	t_com	*command;

	i = 0;
	while (i < length)
	{
		com_name = get_command_name_by_code(code[i++]);
		command = check_command(com_name);
		if (command->is_codage)
			get_args_types_by_codage(code[i++], command);
		else
			set_args_types(command);
		i = read_args_by_types(code, i, command);
		write_args_to_file(fd, command);
		ft_strdel(&com_name);
		ft_memdel((void **)&(command));
	}
}
