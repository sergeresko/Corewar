/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:31 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:32 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_add(t_cw *cw, t_car *car)
{
	int k;
	int	result;
	int	place;
	int	num_reg[3];

	k = 0;
	while (k < 3)
	{
		place = take_arg_place(car, k);
		num_reg[k] = (unsigned char)take_arg_from_field(cw->field, place, 1);
		k += 1;
	}
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | add r%d r%d r%d\n",
		car->num, num_reg[0], num_reg[1], num_reg[2]);*/
	result = car->regs[num_reg[0]] + car->regs[num_reg[1]];
	car->regs[num_reg[2]] = result;
	car->carry = (result == 0) ? 1 : 0;
	replace_c(cw, car);
}
