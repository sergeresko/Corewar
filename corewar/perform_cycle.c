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
**	returns TRUE or FALSE
*/

static int		is_valid_opcode(int code)
{
	return (1 <= code && code <= 16);
}

static void		execute_car(t_vm *vm, t_car *car)
{
	if (car->delay == 0)		// i.e. if `car->place` is at a new position
	{
		car->opcode = vm->field[car->place].square;		// equivalent to `= read_from_field(vm->field, car->place, 1)`
		if (!is_valid_opcode(car->opcode))
		{
			car->place = ++(car->place) % MEM_SIZE;	// advance `car->place` by 1 byte
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
**	successively execute each car
*/

#define FMT		"It is now cycle %d\n"
#define FMT_COL	PF_MAGENTA FMT PF_RESET

void			perform_cycle(t_vm *vm)
{
	t_list		*item;

	++(vm->cycle);				// increment
	if (vm->verbose)
	{
		ft_printf(vm->color ? FMT_COL : FMT, vm->cycle);
	}
	item = vm->cars;
	while (item != NULL)
	{
		execute_car(vm, item->content);
		item = item->next;
	}
}
