/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_register.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:20:47 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:20:47 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	read_register(char **tline, size_t i, t_com *command)
{
	int 	arg;
	int 	checked;
	int		arg_num;

	arg = ft_atoi(&((*tline)[++i]));
	if (g_error_mode || !command)
	{
		ft_printf("Syntax error, register \"r%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(command)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_arg_1(command->name, arg_num, T_REG)) == -1)
	{
		ft_printf("Syntax error, register \"r%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type register for instruction %s\n", arg_num, command->name);
		exit(-1);
	}
	write_arg(command, arg_num, T_REG, arg);
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}
