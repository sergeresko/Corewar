/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:37:26 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 12:36:07 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_revert_integer(t_com *command, int arg_num, int delta)
{
	unsigned int	revert_delta;

	revert_delta = ~delta + 1;
	if (command->arg_types[arg_num] == T_IND)
		return (short_in_hex(revert_delta));
	return (command->label_size == 2
		? short_in_hex(revert_delta)
		: integer_in_hex(revert_delta));
}

int		get_label_index(t_label *labels, char *label_name)
{
	t_label	*temp;

	temp = labels;
	while (temp)
	{
		if (ft_strequ(temp->name, label_name))
			return (temp->index);
		temp = temp->next;
	}
	return (-1);
}

char	*get_label_name(t_label *labels, int index)
{
	t_label	*temp;

	temp = labels;
	while (temp)
	{
		if (temp->index == index)
			return (temp->name);
		temp = temp->next;
	}
	return (NULL);
}

void	print_error(t_asm *asm_struct, int i, char *colon_line)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s:\"\n",
			asm_struct->data.line, i + 1, colon_line);
}

void	check_colon(char *eline, t_asm *asm_struct, int i)
{
	int		j;
	char	*colon_line;

	j = 0;
	if (ft_get_substr_index(eline, ":") == 0)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] "
			"INDIRECT_LABEL \"%s\"\n", asm_struct->data.line, i + 1, eline);
		exit(-1);
	}
	if (eline[0] == '%')
		check_direct_label(eline, asm_struct, i);
	while (eline[j] != ':')
		++j;
	if (!(colon_line = ft_strnew(j)))
		return ;
	j = 0;
	while (eline[j] != ':')
	{
		colon_line[j] = eline[j];
		++j;
	}
	colon_line[j] = eline[j];
	print_error(asm_struct, i, colon_line);
	exit(-1);
}
