/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:53:30 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/27 11:59:00 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// identical to `op_ld` apart from lines marked with "//"

void			op_lld(t_cw *cw, t_car *car)								//
{
	int const	value = get_value(vm, car, 0);
	int const	reg = get_reg(vm, car, 1);

	car->regs[reg] = value;
	car->carry = (value == 0);
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | lld %d r%d\n", car->num, value, reg);*/			//
	car->place = (car->place + car->offset) % MEM_SIZE;
}
