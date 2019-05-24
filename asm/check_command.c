/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/30 00:23:46 by zaliskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_command(char *tline, size_t start, size_t end, t_asm *asm_struct)
{
	char	*name;
	t_com	*command;

	name = ft_strsub(tline, (unsigned int)start, end - start);
	if (!asm_struct->data.got_name || !asm_struct->data.got_description)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION \"%s\"\n",
			   asm_struct->data.line, (int)start + 1, name);
		exit(-1);
	}
	if (!asm_struct->header.hex_name[0] || !asm_struct->header.hex_description[0] || asm_struct->command)
	{
		ft_printf("Syntax error, command %s\n", name);
		exit(-1);
	}
	if (name)
	{
		if ((command = check_command(name)))
			asm_struct->command = command;
		else
		{
			ft_printf("Lexical error: %s\n", name);
		}
	}
	else
		perror("");

}

t_com	*check_command(char *command)
{
	if (ft_strequ("live", command))
		return (make_command_struct(command, 1, FALSE, LABEL_SIZE_4));
	else if (ft_strequ("ld", command))
		return (make_command_struct(command, 2, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("st", command))
		return (make_command_struct(command, 3, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("add", command))
		return (make_command_struct(command, 4, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("sub", command))
		return (make_command_struct(command, 5, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("and", command))
		return (make_command_struct(command, 6, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("or", command))
		return (make_command_struct(command, 7, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("xor", command))
		return (make_command_struct(command, 8, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("zjmp", command))
		return (make_command_struct(command, 9, FALSE, LABEL_SIZE_2));
	else
		return check_command_2(command);
}

t_com	*check_command_2(char *command)
{
	if (ft_strequ("ldi", command))
		return (make_command_struct(command, 10, TRUE, LABEL_SIZE_2));
	if (ft_strequ("sti", command))
		return (make_command_struct(command, 11, TRUE, LABEL_SIZE_2));
	if (ft_strequ("fork", command))
		return (make_command_struct(command, 12, FALSE, LABEL_SIZE_2));
	if (ft_strequ("lld", command))
		return (make_command_struct(command, 13, TRUE, LABEL_SIZE_4));
	if (ft_strequ("lldi", command))
		return (make_command_struct(command, 14, TRUE, LABEL_SIZE_2));
	if (ft_strequ("lfork", command))
		return (make_command_struct(command, 15, FALSE, LABEL_SIZE_2));
	if (ft_strequ("aff", command))
		return (make_command_struct(command, 16, TRUE, LABEL_SIZE_4));
	else
		return (NULL);
}

t_com	*make_command_struct(char *name, char code, char codage, int label_size)
{
	t_com	*new_command_struct;

	if ((new_command_struct = ft_memalloc(sizeof(t_com))))
	{
		new_command_struct->name = name;
		new_command_struct->code = code;
		new_command_struct->is_codage = codage;
		new_command_struct->label_size = label_size;
		return (new_command_struct);
	}
	return (NULL);
}
