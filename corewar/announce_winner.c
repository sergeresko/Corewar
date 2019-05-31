/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:52:22 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 17:56:15 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FMT		"Player %d (%s) won\n"
#define FMT_COL	PF_BOLD FMT PF_RESET

void			announce_winner(t_vm const *vm)
{
	ft_printf(vm->color ? FMT_COL : FMT,
			vm->last_living_champ_id,
			get_champ_by_id(vm->champs, vm->last_living_champ_id)->name);
}
