/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:31 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 20:27:08 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_add(t_vm *vm, t_car *car)
{
	int const	reg_1 = read_from_field(vm->field, car->arg_place[0], 1);
	int const	reg_2 = read_from_field(vm->field, car->arg_place[1], 1);
	int const	value = car->regs[reg_1] + car->regs[reg_2];
	int const	reg_3 = read_from_field(vm->field, car->arg_place[2], 1);

	car->regs[reg_3] = value;
	car->carry = (value == 0);
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | add r%d r%d r%d\n",
		car->num, reg_1, reg_2, reg_3);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
