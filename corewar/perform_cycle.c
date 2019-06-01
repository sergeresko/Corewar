/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:59:05 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 16:35:47 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	TRUE or FALSE
*/

static int		is_valid_opcode(int code)
{
	return (1 <= code && code <= 16);
}

/*
**	if the car is at a new position, read an opcode and, if it is not valid,
**	advance the car by 1 byte and quit, or, otherwise, find out the number of
**	cycles until execution corresponding to the opcode;
**	decrement the number of cycles until execution;
**	if it's time to execute the operation, execute it
*/

static void		execute_car(t_vm *vm, t_car *car)
{
	if (car->delay == 0)
	{
		car->opcode = read_from_field(vm->field, car->place, 1);
		if (!is_valid_opcode(car->opcode))
		{
			car->place = (car->place + 1) % MEM_SIZE;
			return ;
		}
		car->delay = g_ops[car->opcode].delay;
	}
	--(car->delay);
	if (car->delay == 0)
	{
		execute_operation(vm, car);
	}
}

/*
**	increment cycle count;
**	successively execute each car
*/

#define FMT		"It is now cycle %d\n"
#define FMT_COL	PF_MAGENTA FMT PF_RESET

void			perform_cycle(t_vm *vm)
{
	t_list		*item;

	++(vm->cycle);
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT, vm->cycle);
	}
	item = vm->cars;
	while (item != NULL)
	{
		execute_car(vm, item->content);
		item = item->next;
	}
}
