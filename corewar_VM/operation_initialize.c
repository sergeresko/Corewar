/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:57:54 by mdmytro           #+#    #+#             */
/*   Updated: 2019/02/18 16:57:57 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

struct s_core g_core;

static const int16_t	g_cv[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800,\
	10, 50, 1000, 2};

static void	label_take(void)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if ((i >= 8 && i <= 11) || (i >= 13 && i <= 14))
			g_core.oper[i].label = 2;
		else
			g_core.oper[i].label = 4;
	}
}

static void	cycle_value_init(void)
{
	int		i;

	i = -1;
	while (++i < 16)
		g_core.oper[i].cycle_value = g_cv[i];
}

void		operation_initialize(void)
{
	/* g_core.oper[0].f = &cw_live;
	g_core.oper[1].f = &cw_ld;
	g_core.oper[2].f = &cw_st;
	g_core.oper[3].f = &cw_add;
	g_core.oper[4].f = &cw_sub;
	g_core.oper[5].f = &cw_binary_and;
	g_core.oper[6].f = &cw_binary_or;
	g_core.oper[7].f = &cw_binary_xor;
	g_core.oper[8].f = &cw_zjmp;
	g_core.oper[9].f = &cw_ldi;
	g_core.oper[10].f = &cw_sti;
	g_core.oper[11].f = &cw_fork;
	g_core.oper[12].f = &cw_lld;
	g_core.oper[13].f = &cw_lldi;
	g_core.oper[14].f = &cw_lfork;
	g_core.oper[15].f = &cw_aff;*/
	label_take();
	cycle_value_init();
}

