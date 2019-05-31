/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:40:58 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 17:43:59 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	perform_battle(t_vm *vm)
{
	vm->cycle = 0;							// init
	vm->cycle_to_die = CYCLE_TO_DIE;		// init
	vm->nbr_checks = 0;						// init
	// ...
	load_champs(vm);
	while (vm->cars != NULL && vm->cycle != vm->dump_cycle)
	{
		perform_round(vm);
	}
	if (vm->cars == NULL && vm->last_living_champ_id != 0)
	{
		announce_winner(vm);
	}
	if (vm->cycle == vm->dump_cycle)
	{
		dump_memory(vm);
	}
}
