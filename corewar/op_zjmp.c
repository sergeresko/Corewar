/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:19 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 18:04:52 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | zjmp %d %s\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_zjmp(t_vm *vm, t_car *car)
{
	int const	value = get_value(vm, car, 0);

	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				car->id, value, car->carry ? "OK" : "FAILED");
	}
	if (car->carry)
	{
		car->place = (unsigned)(car->place + value % IDX_MOD) % MEM_SIZE;
	}
	else
	{
		advance_car(vm, car);
	}
}
