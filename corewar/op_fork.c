/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:56 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/29 12:51:53 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_fork(t_vm *vm, t_car *car)
{
	(void)vm;
//	int const	address = get_value(vm, car, 0);
//	int const	place = (car->place + (address % IDX_MOD)) % MEM_SIZE;

//	one_more_car(vm, car->prev, place);		// TODO:
//	move_car_body(vm->car, car);			//
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | fork  %d (%d)\n",
		car->id, address, place);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
