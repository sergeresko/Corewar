/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:58:59 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:59:01 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern const t_ops g_ops[16];

void		replace_c(t_cw *cw, t_car *car)
{
	int	new_place;
	int k;

	new_place = car->place + 1;
	k = 0;
	while (k < car->args_nbr)
	{
		new_place += take_amount_by_class(car, k);
		k += 1;
	}
	/*if (cw->ind->actions && !cw->ind->v)
		detailed_car_move(cw, car);*/
	car->place = new_place % MEM_SIZE;
}
