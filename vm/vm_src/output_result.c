/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:20:47 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/20 18:20:49 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	output_result(t_cw *cw)
{
	if (!cw->alive_carry_nbr)
	{
		if (cw->ind->c)
			ft_printf("%s", GREEN);
		ft_printf("CoreWar champion %d, \"%s\" won in this match!\n",
		cw->last_champ->id, cw->last_champ->name);
		if (cw->ind->t)
			system("afplay music/"%WIN_MUSIC%".mp3&");
		if (cw->ind->c)
			ft_printf("%s", DEF);
	}
	if (cw->ind->l)
		system("leaks corewar");
	exit(0);
}
