/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:51:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | or %d %d r%d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_or(t_vm *vm, t_car *car)
{
	int const	operand_1 = get_value(vm, car, 0);
	int const	operand_2 = get_value(vm, car, 1);
	int const	value = operand_1 | operand_2;
	int const	reg = get_reg(vm, car, 2);

	car->regs[reg] = value;
	car->carry = (value == 0);
	if (vm->verbose)
	{
		ft_printf(vm->color ? FMT_COL : FMT,
				car->id, operand_1, operand_2, reg);
	}
	advance_car(vm, car);
}
