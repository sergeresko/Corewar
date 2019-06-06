/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_and_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:37:05 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:07:27 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_args_by_types(char *code, int i, t_com *command)
{
	int		j;

	j = 0;
	while (j < 3)
	{
		if (command->arg_types[j] == T_REG)
			i = read_reg_byt(code, i, command, j);
		else if (command->arg_types[j] == T_DIR)
			i = read_dir_byt(code, i, command, j);
		else if (command->arg_types[j] == T_IND)
			i = read_ind_byt(code, i, command, j);
		j++;
	}
	return (i);
}

int		read_reg_byt(const char *code, int i, t_com *com, int a_n)
{
	com->arguments[a_n] = code[i++];
	return (i);
}

int		read_dir_byt(const char *code, int i, t_com *com, int a_n)
{
	int		j;
	int		direct;

	j = 0;
	direct = 0;
	while (j < com->label_size)
	{
		direct <<= 8;
		direct |= (unsigned char)code[i++];
		j++;
	}
	if (com->label_size == LABEL_SIZE_2)
		com->arguments[a_n] = (short)direct;
	else if (com->label_size == LABEL_SIZE_4)
		com->arguments[a_n] = direct;
	return (i);
}

int		read_ind_byt(const char *code, int i, t_com *com, int a_n)
{
	short	indirect;

	indirect = 0;
	indirect |= (unsigned char)code[i++];
	indirect <<= 8;
	indirect |= (unsigned char)code[i++];
	com->arguments[a_n] = indirect;
	return (i);
}

void	read_code(char *code, int length, int fd)
{
	int		i;
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
