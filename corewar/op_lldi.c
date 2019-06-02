/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:54:51 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:51:13 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT_1	"P %4d | lldi %d %d r%d\n"
#define FMT_2	"       | -> load from %d + %d = %d (with pc %d)\n"
#define FMT		FMT_1 FMT_2
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_lldi(t_vm *vm, t_car *car)
{
	int const	operand_1 = get_value(vm, car, 0);
	int const	operand_2 = get_value(vm, car, 1);
	int const	place = car->place + operand_1 + operand_2;
	int const	value = read_from_field(vm->field, place, 4);
	int const	reg = get_reg(vm, car, 2);

	car->regs[reg] = value;
	car->carry = (value == 0);
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				car->id, operand_1, operand_2, reg,
				operand_1, operand_2, operand_1 + operand_2, place);
	}
	advance_car(vm, car);
}
