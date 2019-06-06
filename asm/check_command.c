/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 12:33:17 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_com(char *tl, size_t st, size_t end, t_asm *asm_str)
{
	char	*name;
	t_com	*command;

	command = NULL;
	name = ft_strsub(tl, (unsigned int)st, end - st);
	if (!asm_str->data.got_name || !asm_str->data.got_description)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] "
				"INSTRUCTION \"%s\"\n", asm_str->data.line, (int)st + 1, name);
		exit(-1);
	}
	if (!asm_str->header.hex_name[0]
		|| !asm_str->header.hex_description[0] || asm_str->command)
	{
		ft_printf("Syntax error, command %s\n", name);
		exit(-1);
	}
	read_com_2(name, command, asm_str);
}

void	read_com_2(char *n, t_com *com, t_asm *asm_str)
{
	if (n)
	{
		if ((com = check_command(n)))
			asm_str->command = com;
		else
		{
			ft_printf("Lexical error: %s\n", n);
			exit(-1);
		}
	}
	else
		perror("read_com_2");
}

t_com	*check_command(char *command)
{
	if (ft_strequ("live", command))
		return (make_com_struct(command, 1, FALSE, LABEL_SIZE_4));
	else if (ft_strequ("ld", command))
		return (make_com_struct(command, 2, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("st", command))
		return (make_com_struct(command, 3, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("add", command))
		return (make_com_struct(command, 4, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("sub", command))
		return (make_com_struct(command, 5, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("and", command))
		return (make_com_struct(command, 6, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("or", command))
		return (make_com_struct(command, 7, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("xor", command))
		return (make_com_struct(command, 8, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("zjmp", command))
		return (make_com_struct(command, 9, FALSE, LABEL_SIZE_2));
	else
		return (check_command_2(command));
}

t_com	*check_command_2(char *command)
{
	if (ft_strequ("ldi", command))
		return (make_com_struct(command, 10, TRUE, LABEL_SIZE_2));
	if (ft_strequ("sti", command))
		return (make_com_struct(command, 11, TRUE, LABEL_SIZE_2));
	if (ft_strequ("fork", command))
		return (make_com_struct(command, 12, FALSE, LABEL_SIZE_2));
	if (ft_strequ("lld", command))
		return (make_com_struct(command, 13, TRUE, LABEL_SIZE_4));
	if (ft_strequ("lldi", command))
		return (make_com_struct(command, 14, TRUE, LABEL_SIZE_2));
	if (ft_strequ("lfork", command))
		return (make_com_struct(command, 15, FALSE, LABEL_SIZE_2));
	if (ft_strequ("aff", command))
		return (make_com_struct(command, 16, TRUE, LABEL_SIZE_4));
	else
		return (NULL);
}

t_com	*make_com_struct(char *n, char code, char codg, int l_size)
{
	t_com	*new_command_struct;

	if ((new_command_struct = ft_memalloc(sizeof(t_com))))
	{
		new_command_struct->name = n;
		new_command_struct->code = code;
		new_command_struct->is_codage = codg;
		new_command_struct->label_size = l_size;
		return (new_command_struct);
	}
	return (NULL);
}
