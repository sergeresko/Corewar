/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:56 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 16:05:57 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_fork(t_cw *cw, t_car *car)
{
	int				address;
	int				place;

	address = take_arg_by_class(cw, car, 0);
	place = car->place + (address % IDX_MOD);
	place %= MEM_SIZE;
	one_more_car(cw, car->prev, place);
	move_car_body(cw->car, car);
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | fork  %d (%d)\n",
		car->num, address, place);*/
	replace_c(cw, car);
}
