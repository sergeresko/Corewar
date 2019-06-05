/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indirect_label.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:25:52 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/04 00:45:52 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	syntax_error_indirect(char *label)
{
	ft_printf("Syntax error, indirect_label \"%%:%s\"\n", label);
	exit(-1);
}

void	argument_error(int arg_num)
{
	ft_printf("Argument number - %d\n", arg_num);
	exit(-1);
}

int		read_indirect_label(char **tline, int i, t_com *command)
{
	int		j;
	int		arg_num;
	int		checked;
	char	*label;

	if ((j = check_label(*tline, ++i, FALSE)))
	{
		label = ft_strsub(*tline, i, j - i);
		if (g_error_mode || !command)
			syntax_error_indirect(label);
		if ((arg_num = get_arg_num(command)) == -1)
			argument_error(arg_num);
		if ((checked = check_arg_1(command->name, arg_num, T_IND)) == -1)
			syntax_error_indirect(label);
		if (!checked)
		{
			ft_printf("Invalid parameter %d type indirect for instruction %s\n",
					arg_num, command->name);
			exit(-1);
		}
		write_l_a(command, arg_num, T_IND, &label);
		return (check_proper_ending(*tline, j));
	}
	return (i);
}

int		is_label_num_start(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == LABEL_CHAR)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
