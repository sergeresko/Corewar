/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:43 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:50:35 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | ldi %d %d r%d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_ldi(t_vm *vm, t_car *car)
{
	int const	operand_1 = get_value(vm, car, 0);
	int const	operand_2 = get_value(vm, car, 1);
	int const	place = car->place + (operand_1 + operand_2) % IDX_MOD;
	int const	value = read_from_field(vm->field, place, 4);
	int const	reg = get_reg(vm, car, 2);

	car->regs[reg] = value;
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				car->id, operand_1, operand_2, reg);
	}
	advance_car(vm, car);
}
