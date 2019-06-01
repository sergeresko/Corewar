/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:09 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:50:07 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | ld %d r%d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_ld(t_vm *vm, t_car *car)
{
	int const	value = get_value(vm, car, 0);
	int const	reg = get_reg(vm, car, 1);

	car->regs[reg] = value;
	car->carry = (value == 0);
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, car->id, value, reg);
	}
	advance_car(vm, car);
}
