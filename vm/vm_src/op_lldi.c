/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:54:51 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:54:52 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_lldi(t_cw *cw, t_car *car)
{
	int	amount1;
	int	amount2;
	int	place;
	int	num_reg;

	amount1 = take_arg_by_class(cw, car, 0);
	amount2 = take_arg_by_class(cw, car, 1);
	place = take_arg_place(car, 2);
	num_reg = (unsigned char)take_arg_from_field(cw->field, place, 1);
	place = car->place - 1 + ((amount1 + amount2));
	car->regs[num_reg] = take_arg_from_field(cw->field, place, 4);
	/*if (!cw->ind->v && cw->ind->ops)
	{
		ft_printf("P %4d | lldi %d %d r%d\n",
		car->num, amount1, amount2, num_reg);
	}*/
	replace_c(cw, car);
}
