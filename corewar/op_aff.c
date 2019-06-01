/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:48:38 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"Aff: %c\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_aff(t_vm *vm, t_car *car)
{
	int const	reg = get_reg(vm, car, 0);
	int const	value = car->regs[reg];

	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, (char)value);
	}
	advance_car(vm, car);
}
