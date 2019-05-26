/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 20:56:28 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_aff(t_vm *vm, t_car *car)
{
	int const	reg = read_from_field(vm->field, car->arg_place[0], 1);
	int const	value = car->regs[reg];

	/*if (!vm->ind->v)		// ??
	{
		ft_printf("Aff: %c\n", (char)value);
	}*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
