/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:37 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:52:27 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_sub(t_vm *vm, t_car *car)
{
	int const	reg_1 = get_reg(vm, car, 0);
	int const	reg_2 = get_reg(vm, car, 1);
	int const	value = car->regs[reg_1] - car->regs[reg_2];
	int const	reg_3 = get_reg(vm, car, 2);

	car->regs[reg_3] = value;
	car->carry = (value == 0);
	//if (!vm->ind->v && vm->ind->ops)
	if (vm->verbose)
	{
		ft_printf("P %4d | sub r%d r%d r%d\n",
				car->id, reg_1, reg_2, reg_3);
	}
	advance_car(vm, car);
}
