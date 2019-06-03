/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:06:01 by omaiko            #+#    #+#             */
/*   Updated: 2019/06/02 13:06:30 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | lfork %d (%d)\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_lfork(t_vm *vm, t_car *car)
{
	int const	address = get_value(vm, car, 0);
	int const	place = car->place + address;

	list_push(&(vm->cars), clone_car(car, place));
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, car->id, address, place);
	}
	advance_car(vm, car);
}
