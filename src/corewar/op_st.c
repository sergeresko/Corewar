/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:18 by omaiko            #+#    #+#             */
/*   Updated: 2019/06/01 22:12:39 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | st r%d %d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_st(t_vm *vm, t_car *car)
{
	int const	reg = get_reg(vm, car, 0);
	int const	value = car->regs[reg];
	int			addr;

	if (car->arg_class[1] == T_REG)
	{
		addr = get_reg(vm, car, 1);
		car->regs[addr] = value;
	}
	else
	{
		addr = (short)read_from_field(vm->field, car->arg_place[1], IND_SIZE);
		write_to_field(vm->field, car, addr % IDX_MOD, value);
	}
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, car->id, reg, addr);
	}
	advance_car(vm, car);
}
