/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:18 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:20 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_st(t_cw *cw, t_car *car)
{
	int				address;
	int				place;
	int				support;
	unsigned char	register_num;

	place = car->place + 1;
	register_num = (unsigned char)take_arg_from_field(cw->field, place, 1);
	support = car->regs[register_num];
	if (car->arg_class[1] == T_REG)
	{
		address = take_arg_by_class(cw, car, 1);
		car->regs[address] = support;
	}
	else
	{
		place = take_arg_place(car, 1);
		address = (short)take_arg_from_field(cw->field, place, IND_SIZE);
		address %= IDX_MOD;
	}
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | st r%d %d\n",
		car->num, register_num, address);*/
	replace_c(cw, car);
}
