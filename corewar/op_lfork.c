/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:06:01 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 16:13:05 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"P %4d | lfork %d (%d)\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_lfork(t_vm *vm, t_car *car)
{
	int const	address = get_value(vm, car, 0);
	int const	place = (unsigned)(car->place + address) % MEM_SIZE;

	list_push(&(vm->cars), clone_car(car, place));
	if (vm->verbose)
	{
		ft_printf(vm->color ? FMT_COL : FMT, car->id, address, place);
	}
	car->place = (car->place + car->offset) % MEM_SIZE;
}
