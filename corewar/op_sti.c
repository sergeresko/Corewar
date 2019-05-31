/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:51 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:52:16 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | sti r%d %d %d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_sti(t_vm *vm, t_car *car)
{
	int const	reg = get_reg(vm, car, 0);
	int const	value = car->regs[reg];
	int const	operand_1 = get_value(vm, car, 1);
	int const	operand_2 = get_value(vm, car, 2);
	int const	address = (operand_1 + operand_2) % IDX_MOD;

	write_to_field(vm->field, car->place + address, value);
	if (vm->verbose)
	{
		ft_printf(vm->color ? FMT_COL : FMT,
				car->id, reg, operand_1, operand_2);
	}
	advance_car(vm, car);
}
