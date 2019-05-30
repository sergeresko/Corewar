/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:56 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 16:12:36 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_fork(t_vm *vm, t_car *car)
{
	int const	address = get_value(vm, car, 0);
	int const	place = (unsigned)(car->place + (address % IDX_MOD)) % MEM_SIZE;
	t_car 		*new_car;

	new_car = clone_car(car, place);
	list_push(&(vm->cars), new_car);
	//if (!vm->ind->v && vm->ind->ops)
	if (vm->verbose)
	{
		ft_printf("P %4d | fork %d (%d)\n", car->id, address, place);
	}
	car->place = (car->place + car->offset) % MEM_SIZE;
}
