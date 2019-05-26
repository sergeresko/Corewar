/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:05:51 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 16:05:52 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_sti(t_cw *cw, t_car *car)
{
	int				second_arg;
	int				third_arg;
	int				place;
	int				amount;
	unsigned char	register_num;

	place = car->place + 1;
	register_num = (unsigned char)take_arg_from_field(cw->field, place, 1);
	amount = car->regs[register_num];
	second_arg = take_arg_by_class(cw, car, 1);
	third_arg = take_arg_by_class(cw, car, 2);
	rewrite_field(cw, car, amount, (second_arg + third_arg) % IDX_MOD);
	/*if (!cw->ind->v && cw->ind->ops)
	{
		ft_printf("P %4d | sti r%d %d %d\n",
		car->num, register_num, second_arg, third_arg);
	}*/
	replace_c(cw, car);
}
