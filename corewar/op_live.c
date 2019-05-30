/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:50:57 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 18:02:58 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	live_champ(t_vm *vm, int champ_id)
{
	//if (cw->ind->v)
	//{
	//	smth
	//}
	vm->last_living_champ_id = champ_id;
	//if (cw->ind->lives && !cw->ind->v)
	if (vm->verbose)
	{
		ft_printf("A process shows that player %d (%s) is alive\n",
				champ_id, get_champ_by_id(vm->champs, champ_id)->name);
	}
}

void		op_live(t_vm *vm, t_car *car)
{
	int const	value = get_value(vm, car, 0);

	++(vm->nbr_live);
	car->cycle_when_last_live = vm->cycle;
	//if (cw->ind->ops && !cw->ind->v)
	if (vm->verbose)
	{
		ft_printf("P %4d | live %d\n", car->id, value);
	}
	if (value < 0 && -value <= vm->champ_amount)
	{
		live_champ(vm, -value);
	}
	advance_car(vm, car);
}
