/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:32:17 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/29 16:33:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	return the size in bytes of the `arg`th argument (starting from 0)
**	of the operation that has been parsed by `car`;
**	if the argument's class is invalid, return 0
*/

int				get_arg_size(t_car const *car, int arg)
{
	int const	class = car->arg_class[arg];

	if (class == T_DIR)
	{
		return (g_ops[car->opcode].dir_size);
	}
	if (class == T_IND)
	{
		return (IND_SIZE);
	}
	if (class == T_REG)
	{
		return (1);
	}
	return (0);
}
