/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indir.c                                       :+:      :+:    :+:   */
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

int		read_indir(char **tl, int i, t_com *com, t_asm *a_str)
{
	int		arg;
	int		arg_num;
	int		checked;

	if ((*tl)[i] == LABEL_CHAR)
		return (read_indirect_label(tl, i, com));
	if (is_label_num_start(*tl, i))
		return (read_string(tl, i, a_str));
	check_for_proper_arg(*tl, i);
	if ((arg = ft_atoi(&((*tl)[i]))) && (g_error_mode || !com))
		indirect_syntax(arg);
	if ((arg_num = get_arg_num(com)) == -1)
		indirect_argument(arg_num);
	if ((checked = check_arg_1(com->name, arg_num, T_IND)) == -1)
		indirect(arg);
	if (!checked)
		indirect_invalid(arg_num, com->name);
	write_arg(com, arg_num, T_IND, arg);
	i += (*tl)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tl)[i]))
		i++;
	return (check_proper_ending(*tl, i));
}
