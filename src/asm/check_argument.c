/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:35:52 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_register(char *tline, size_t i)
{
	if (ft_isdigit(tline[++i]))
	{
		i += !ft_isdigit(tline[i + 1]) ? 1 : 2;
		if (tline[i] == ' ' || tline[i] == '\t'
			|| tline[i] == '\n' || tline[i] == '\0'
				|| tline[i] == SEPARATOR_CHAR)
			return (TRUE);
	}
	return (FALSE);
}

int		get_arg_num(t_com *command)
{
	if (!command->arg_types[0])
		return (0);
	if (!command->arg_types[1])
		return (1);
	if (!command->arg_types[2])
		return (2);
	return (-1);
}

int		is_arg(const t_arg_type *arg_ts, t_arg_type arg_t)
{
	int		i;

	i = 0;
	if (!arg_ts[0] && !arg_ts[1] && !arg_ts[2])
		return (-1);
	while (i < 3)
	{
		if (arg_ts[i] && arg_ts[i] == arg_t)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		check_arg_1(char *com, int a_n, t_arg_type a_t)
{
	if (ft_strequ(com, "live"))
		return (is_arg(g_live[a_n], a_t));
	else if (ft_strequ(com, "ld"))
		return (is_arg(g_ld[a_n], a_t));
	else if (ft_strequ(com, "st"))
		return (is_arg(g_st[a_n], a_t));
	else if (ft_strequ(com, "add"))
		return (is_arg(g_add[a_n], a_t));
	else if (ft_strequ(com, "sub"))
		return (is_arg(g_sub[a_n], a_t));
	else if (ft_strequ(com, "and"))
		return (is_arg(g_and[a_n], a_t));
	else if (ft_strequ(com, "or"))
		return (is_arg(g_or[a_n], a_t));
	else if (ft_strequ(com, "xor"))
		return (is_arg(g_xor[a_n], a_t));
	else if (ft_strequ(com, "zjmp"))
		return (is_arg(g_zjmp[a_n], a_t));
	else if (ft_strequ(com, "ldi"))
		return (is_arg(g_ldi[a_n], a_t));
	else
		return (check_arg_2(com, a_n, a_t));
}

int		check_arg_2(char *com, int a_n, t_arg_type a_t)
{
	if (ft_strequ(com, "sti"))
		return (is_arg(g_sti[a_n], a_t));
	else if (ft_strequ(com, "fork"))
		return (is_arg(g_fork[a_n], a_t));
	else if (ft_strequ(com, "lld"))
		return (is_arg(g_lld[a_n], a_t));
	else if (ft_strequ(com, "lldi"))
		return (is_arg(g_lldi[a_n], a_t));
	else if (ft_strequ(com, "lfork"))
		return (is_arg(g_lfork[a_n], a_t));
	else if (ft_strequ(com, "aff"))
		return (is_arg(g_aff[a_n], a_t));
	else
	{
		ft_printf("Unknown command %s! Exiting..\n", com);
		exit(-1);
	}
}
