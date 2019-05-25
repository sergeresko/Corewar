/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:09 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:10 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_ld(t_cw *cw, t_car *car)
{
	int	support;
	int	place;
	int	num_reg;

	support = take_arg_by_class(cw, car, 0);
	place = take_arg_place(car, 1);
	num_reg = (unsigned char)take_arg_from_field(cw->field, place, 1);
	car->carry = (support == 0) ? 1 : 0;
	car->regs[num_reg] = support;
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | ld %d r%d\n", car->num, support, num_reg);*/
	replace_c(cw, car);
}
