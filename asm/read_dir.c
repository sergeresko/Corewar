/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:23:14 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/02 01:40:30 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	read_dir_addon(int arg, int arg_num, int checked, t_com *com)
{
	if (arg_num == -1)
		ft_printf("Argument number - %d\n", arg_num);
	else if (checked == -1)
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
	else if (!checked)
		ft_printf("Invalid parameter %d type direct for instruction %s\n",
				arg_num, com->name);
	else
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
	exit(-1);
}

int		read_dir(char **tl, int i, t_com *com)
{
	int		arg;
	int		arg_num;
	int		checked;

	if ((*tl)[++i] == LABEL_CHAR)
		return (read_direct_label(tl, i, com));
	arg = ft_atoi(&((*tl)[i]));
	if (g_error_mode || !com || ((arg_num = get_argument_number(com)) == -1)
	|| ((checked = check_arg_1(com->name, arg_num, T_DIR)) == -1) || !checked)
	{
		read_dir_addon(arg, arg_num, checked, com);
	}
	write_arg(com, arg_num, T_DIR, arg);
	i += (*tl)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tl)[i]))
		i++;
	return (check_proper_ending(*tl, i));
}
