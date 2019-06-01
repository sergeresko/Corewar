/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:56 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 17:49:40 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | fork %d (%d)\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_fork(t_vm *vm, t_car *car)
{
	int const	address = get_value(vm, car, 0);
	int const	place = (unsigned)(car->place + address % IDX_MOD) % MEM_SIZE;

	list_push(&vm->cars, clone_car(car, place));
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, car->id, address, place);
	}
	advance_car(vm, car);
}
