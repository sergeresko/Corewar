/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:12:06 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 16:35:02 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"Process %d hasn't lived for %d cycles (CTD %d)\n"
#define FMT_COL	PF_RED FMT PF_RESET

/*
**	kill all cars that haven't executed `live` since the previous check
*/

void			perform_check(t_vm *vm)
{
	int const	oldest_cycle = vm->cycle - vm->cycle_to_die;
	t_list		**addr;
	t_car		*car;

	++(vm->nbr_checks);
	addr = &vm->cars;
	while (*addr != NULL)
	{
		car = (*addr)->content;
		if (car->cycle_when_last_live <= oldest_cycle)
		{
			if (vm->verbose)
			{
				ft_printf(vm->color ? FMT_COL : FMT,
						car->id, vm->cycle - car->cycle_when_last_live,
						vm->cycle_to_die);
			}
			free(list_pop(addr));
		}
		else
		{
			addr = &(*addr)->next;
		}
	}
}
