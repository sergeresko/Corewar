/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_dump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 12:37:00 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	set `vm->dump_cycles` to the value of the dump option
**	(or leave it as it is (-1) if this option is not present);
**	set `vm->dump_bytes` to 32 for "-dump" or "-dump32"
**	and to 64 for "-dump64"
*/

char			**get_opt_dump(t_vm *vm, char **av)
{
	char		*arg;

	if ((arg = *(++av)) != NULL)
	{
		if (ft_strequ(arg, "-dump") || ft_strequ(arg, "-dump32"))
		{
			vm->dump_bytes = 32;
		}
		else if (ft_strequ(arg, "-dump64"))
		{
			vm->dump_bytes = 64;
		}
		else
		{
			return (av - 1);
		}
		if ((arg = *(++av)) == NULL || !is_only_digits(arg)
				|| (vm->dump_cycle = ft_atoi(arg)) < 0)
		{
			fatal_error("Invalid value for dump option");
		}
		return (av);
	}
	return (av - 1);
}
