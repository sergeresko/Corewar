/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 11:39:53 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		includes(const char *str, char c)
{
	if (!c || !str || !(*str))
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

char	*convert_int_to_hex(int num)
{
	int		num_len;
	int		res_len;
	char	*result;
	char	*number;

	result = NULL;
	if ((number = ft_itoa_base(num, 16)))
	{
		num_len = ft_strlen(number);
		if ((result = ft_strnew(9)))
		{
			res_len = 8;
			result = ft_memset((void *)result, '0', res_len);
			while (num_len > 0)
				result[--res_len] = ft_tolower(number[--num_len]);
		}
		ft_strdel(&number);
	}
	return (result);
}

void	check_command_arguments(t_com *command)
{
	int		i;
	int		is_error;

	i = 0;
	is_error = FALSE;
	if (!command->arg_types[0])
	{
		ft_printf("Command '%s' has no arguments\n", command->name);
		exit(-1);
	}
	while (i < 3)
	{
		if (!check_arg_1(command->name, i, command->arg_types[i]))
		{
			is_error = TRUE;
			break ;
		}
		i++;
	}
	if (is_error)
	{
		ft_printf("Command '%s' has not proper arguments\n", command->name);
		exit(-1);
	}
}
