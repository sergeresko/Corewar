/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_round.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:27:29 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 12:57:06 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"Cycle to die is now %d\n"
#define FMT_COL	PF_MAGENTA FMT PF_RESET

/*
**	compute the cycle at the end of which the next check has to be performed
*/

static int		compute_last_cycle(t_vm const *vm)
{
	int const	round_duration = (vm->cycle_to_die > 0) ? vm->cycle_to_die : 1;

	return (vm->cycle + round_duration);
}

/*
**	perform the necessary number of cycles and then perform a check;
**	decrease cycle to die if necessary
*/

void			perform_round(t_vm *vm)
{
	int const	last_cycle = compute_last_cycle(vm);

	vm->nbr_live = 0;
	while (vm->cycle < last_cycle)
	{
		if (vm->cycle == vm->dump_cycle)
		{
			return ;
		}
		if (vm->cycle == vm->interactive_cycle)
		{
			interactive_get(vm);
		}
		perform_cycle(vm);
	}
	perform_check(vm);
	if (vm->nbr_live >= NBR_LIVE || vm->nbr_checks == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_checks = 0;
		if (vm->opt.verbose)
		{
			ft_printf(vm->opt.color ? FMT_COL : FMT, vm->cycle_to_die);
		}
	}
}
