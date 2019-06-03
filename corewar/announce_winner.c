/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:52:22 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/02 17:15:18 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT			"Player %d (%s) won\n"
#define FMT_COL		PF_BOLD FMT PF_RESET

#define FMT_CAN		"Contestant %d, \"%s\", has won !\n"
#define FMT_CAN_COL	PF_BOLD FMT_CAN PF_RESET

void			announce_winner(t_vm const *vm)
{
	int const	champ_id = vm->last_living_champ_id;

	if (vm->opt.color)
	{
		ft_putstr(g_champ_colors[champ_id]);
	}
	if (vm->opt.canonic)
	{
		ft_printf(vm->opt.color ? FMT_CAN_COL : FMT_CAN,
				champ_id, get_champ_by_id(vm->champs, champ_id)->name);
	}
	else
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				champ_id, get_champ_by_id(vm->champs, champ_id)->name);
	}
}
