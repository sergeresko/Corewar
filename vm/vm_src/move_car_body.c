/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_car_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 16:23:27 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 16:23:29 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	move_car_body(t_car *where, t_car *from)
{
	int	k;

	k = 1;
	while (k < REG_NUMBER)
	{
		where->regs[k] = from->regs[k];
		k += 1;
	}
	where->arg_class[0] = from->arg_class[0];
	where->arg_class[1] = from->arg_class[2];
	where->arg_class[2] = from->arg_class[2];
	where->carry = from->carry;
	where->recent_cycle = from->recent_cycle;
	where->now_live = from->now_live;
}
