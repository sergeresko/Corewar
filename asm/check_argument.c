/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:19:18 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 	is_register(char *tline, size_t i)
{
	if (ft_isdigit(tline[++i]))
	{
		i += !ft_isdigit(tline[i + 1]) ? 1 : 2;
		if (tline[i] == ' ' || tline[i] == '\t' || tline[i] == '\n' || tline[i] == '\0' || tline[i] == SEPARATOR_CHAR)
			return (TRUE);
	}
	return (FALSE);
}

int 	get_argument_number(t_com *command)
{
	if (!command->arg_types[0])
		return (0);
	if (!command->arg_types[1])
		return (1);
	if (!command->arg_types[2])
		return (2);
	return (-1);
}

int 	is_argument_possible(const t_arg_type arg_types[], t_arg_type arg_type)
{
	int 	i;

	i = 0;
	if (!arg_types[0] && !arg_types[1] && !arg_types[2])
		return (-1);
	while (i < 3)
	{
		if (arg_types[i] == arg_type)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int 	check_argument_1(char *command, int arg_num, t_arg_type arg_type)
{
	if (ft_strequ(command, "live"))
		return (is_argument_possible(g_live[arg_num], arg_type));
	else if (ft_strequ(command, "ld"))
		return (is_argument_possible(g_ld[arg_num], arg_type));
	else if (ft_strequ(command, "st"))
		return (is_argument_possible(g_st[arg_num], arg_type));
	else if (ft_strequ(command, "add"))
		return (is_argument_possible(g_add[arg_num], arg_type));
	else if (ft_strequ(command, "sub"))
		return (is_argument_possible(g_sub[arg_num], arg_type));
	else if (ft_strequ(command, "and"))
		return (is_argument_possible(g_and[arg_num], arg_type));
	else if (ft_strequ(command, "or"))
		return (is_argument_possible(g_or[arg_num], arg_type));
	else if (ft_strequ(command, "xor"))
		return (is_argument_possible(g_xor[arg_num], arg_type));
	else if (ft_strequ(command, "zjmp"))
		return (is_argument_possible(g_zjmp[arg_num], arg_type));
	else if (ft_strequ(command, "ldi"))
		return (is_argument_possible(g_ldi[arg_num], arg_type));
	else
		return check_argument_2(command, arg_num, arg_type);
}

int 	check_argument_2(char *command, int arg_num, t_arg_type arg_type)
{
	if (ft_strequ(command, "sti"))
		return (is_argument_possible(g_sti[arg_num], arg_type));
	else if (ft_strequ(command, "fork"))
		return (is_argument_possible(g_fork[arg_num], arg_type));
	else if (ft_strequ(command, "lld"))
		return (is_argument_possible(g_lld[arg_num], arg_type));
	else if (ft_strequ(command, "lldi"))
		return (is_argument_possible(g_lldi[arg_num], arg_type));
	else if (ft_strequ(command, "lfork"))
		return (is_argument_possible(g_lfork[arg_num], arg_type));
	else if (ft_strequ(command, "aff"))
		return (is_argument_possible(g_aff[arg_num], arg_type));
	else
	{
		ft_printf("Unknown command %s! Exiting..\n", command);
		exit(-1);
	}
}
