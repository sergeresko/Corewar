/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:25:09 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/04 00:45:52 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	indirect_invalid(int arg_num, char *command)
{
	ft_printf("Invalid parameter %d type indirect for instruction %s\n",
		arg_num, command);
	exit(-1);
}

void	indirect_syntax(int arg)
{
	ft_printf("Syntax error, indirect \"%d\"\n", arg);
	exit(-1);
}

void	indirect_argument(int arg_num)
{
	ft_printf("Argument number - %d\n", arg_num);
	exit(-1);
}

void	indirect(int arg)
{
	ft_printf("Syntax error, indirect \"%d\"\n", arg);
	exit(-1);
}

int		read_indirect(char **tline, int i, t_com *command, t_asm *asm_struct)
{
	int		arg;
	int		arg_num;
	int		checked;

	if ((*tline)[i] == LABEL_CHAR)
		return (read_indirect_label(tline, i, command));
	if (is_label_num_start(*tline, i))
		return (read_string(tline, i, asm_struct));
	check_for_proper_arg(*tline, i);
	if ((arg = ft_atoi(&((*tline)[i]))) && (g_error_mode || !command))
		indirect_syntax(arg);
	if ((arg_num = get_arg_num(command)) == -1)
		indirect_argument(arg_num);
	if ((checked = check_arg_1(command->name, arg_num, T_IND)) == -1)
		indirect(arg);
	if (!checked)
		indirect_invalid(arg_num, command->name);
	write_arg(command, arg_num, T_IND, arg);
	i += (*tline)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}
