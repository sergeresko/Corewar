/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:09 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 20:23:12 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_ld(t_vm *vm, t_car *car)
{
	int const	value = get_arg_value(vm, car, 0);
	int const	reg = read_from_field(vm->field, car->arg_place[1], 1);

	car->regs[reg] = value;
	car->carry = (value == 0);
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | ld %d r%d\n", car->num, value, reg);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
