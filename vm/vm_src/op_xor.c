/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:55 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/27 11:57:56 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_xor(t_vm *vm, t_car *car)
{
	int const	operand_1 = get_value(vm, car, 0);
	int const	operand_2 = get_value(vm, car, 1);
	int const	value = operand_1 ^ operand_2;
	int const	reg = get_reg(vm, car, 2);

	car->regs[reg] = value;
	car->carry = (value == 0);
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | xor %d %d r%d\n",
		car->num, operand_1, operand_2, reg);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
