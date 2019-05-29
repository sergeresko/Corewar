/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/29 12:52:18 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_aff(t_vm *vm, t_car *car)
{
	int const	reg = get_reg(vm, car, 0);
	int const	value = car->regs[reg];

	//if (!vm->ind->v)
	if (vm->verbose)
	{
		ft_printf("Aff: %c\n", (char)value);		// maybe change message
	}
	car->place = (car->place + car->offset) % MEM_SIZE;
}
