/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:51 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_or(t_cw *cw, t_car *car)
{
	int				parameter1;
	int				parameter2;
	int				place;
	unsigned char	register_num;

	parameter1 = take_arg_by_class(cw, car, 0);
	parameter2 = take_arg_by_class(cw, car, 1);
	place = take_arg_place(car, 2);
	register_num = (unsigned char)take_arg_from_field(cw->field, place, 1);
	car->regs[register_num] = parameter1 | parameter2;
	car->carry = (car->regs[register_num] == 0) ? 1 : 0;
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | or %d %d r%d\n",
		car->num, parameter1, parameter2, register_num);*/
	replace_c(cw, car);
}
