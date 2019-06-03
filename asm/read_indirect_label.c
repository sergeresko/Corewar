/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indirect_label.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:25:52 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:25:52 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_indirect_label(char **tline, int i, t_com *command)
{
	int 	j;
	int 	arg_num;
	int 	checked;
	char	*label;

	if ((j = check_label(*tline, ++i, FALSE)))
	{
		label = ft_strsub(*tline, i, j - i);
		if (g_error_mode || !command)
		{
			ft_printf("Syntax error, indirect_label \"%%:%s\"\n", label);
			exit(-1);
		}
		if ((arg_num = get_argument_number(command)) == -1)
		{
			ft_printf("Argument number - %d\n", arg_num);
			exit(-1);
		}
		if ((checked = check_arg_1(command->name, arg_num, T_IND)) == -1)
		{
			ft_printf("Syntax error, indirect \"%%:%s\"\n", label);
			exit(-1);
		}
		if (!checked)
		{
			ft_printf("Invalid parameter %d type indirect for instruction %s\n", arg_num, command->name);
			exit(-1);
		}
		write_l_a(command, arg_num, T_IND, &label);
		return (check_proper_ending(*tline, j));
	}
	return (i);
}
