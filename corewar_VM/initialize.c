/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:25:20 by mdmytro           #+#    #+#             */
/*   Updated: 2019/03/04 14:25:22 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_champ_file(t_champ_file *cf)
{
	cf->ch = NULL;
	cf->reserve = 0;
	cf->count_ch = 0;
	cf->hand_brake = 0;
	ft_bzero(cf->flag, 3);
	ft_bzero(cf->flag_quant_ch, MAX_PLAYERS);
}

void		initialize(void)
{
	init_champ_file(&g_core.pd);
	operation_initialize();
	g_core.vp = NULL;
	g_core.cycle = 0;
	g_core.cycle_to_die = CYCLE_TO_DIE;
	g_core.check_ctd = CYCLE_TO_DIE;
	g_core.identifi_max_check = MAX_CHECKS;
	g_core.proces_count = 0;
	g_core.rep_alive = -1;
	g_core.game_over = 1;
}
