/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:23:14 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:23:14 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	read_dir(char **tl, int i, t_com *com, t_asm *asm_struct)
{
	int 	arg;
	int 	arg_num;
	int 	checked;

	if ((*tl)[++i] == LABEL_CHAR)
		return read_direct_label(tl, i, com);
	arg = ft_atoi(&((*tl)[i]));
	if (g_error_mode || !com)
	{
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(com)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_arg_1(com->name, arg_num, T_DIR)) == -1)
	{
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type direct for instruction %s\n", arg_num, com->name);
		exit(-1);
	}
	write_arg(com, arg_num, T_DIR, arg);
	i += (*tl)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tl)[i]))
		i++;
	return (check_proper_ending(*tl, i));
}
