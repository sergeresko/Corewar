/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:25:09 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:25:09 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_indirect(char **tline, int i, t_com *command)
{
	int 	arg;
	int 	arg_num;
	int 	checked;

	if ((*tline)[i] == LABEL_CHAR)
		return read_indirect_label(tline, i, command);
	arg = ft_atoi(&((*tline)[i]));
	if (g_error_mode || !command)
	{
		ft_printf("Syntax error, indirect \"%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(command)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_arg_1(command->name, arg_num, T_IND)) == -1)
	{
		ft_printf("Syntax error, indirect \"%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type indirect for instruction %s\n", arg_num, command->name);
		exit(-1);
	}
	write_arg(command, arg_num, T_IND, arg);
	i += (*tline)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}
