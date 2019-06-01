/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:50:57 by omaiko            #+#    #+#             */
/*   Updated: 2019/06/01 18:22:30 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define MSG		"A process shows that player %d (%s) is alive\n"
#define MSG_COL	PF_GREEN MSG PF_RESET

static void		live_champ(t_vm *vm, int champ_id)
{
	vm->last_living_champ_id = champ_id;
	if (!vm->silent)
	{
		ft_printf(vm->color ? MSG_COL : MSG,
				champ_id, get_champ_by_id(vm->champs, champ_id)->name);
	}
}

#define FMT		"P %4d | live %d\n"
#define FMT_COL	PF_YELLOW FMT PF_RESET

void			op_live(t_vm *vm, t_car *car)
{
	int const	value = get_value(vm, car, 0);

	++(vm->nbr_live);
	car->cycle_when_last_live = vm->cycle;
	if (vm->verbose)
	{
		ft_printf(vm->color ? FMT_COL : FMT, car->id, value);
	}
	if (value < 0 && -value <= vm->champ_amount)
	{
		live_champ(vm, -value);
	}
	advance_car(vm, car);
}
