/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:31 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/27 11:56:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_add(t_vm *vm, t_car *car)
{
	int const	reg_1 = get_reg(vm, car, 0);
	int const	reg_2 = get_reg(vm, car, 1);
	int const	value = car->regs[reg_1] + car->regs[reg_2];
	int const	reg_3 = get_reg(vm, car, 2);

	car->regs[reg_3] = value;
	car->carry = (value == 0);
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | add r%d r%d r%d\n",
		car->id, reg_1, reg_2, reg_3);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
