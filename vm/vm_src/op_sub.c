/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:37 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:39 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_sub(t_cw *cw, t_car *car)
{
	int k;
	int	temp;
	int	place;
	int	num_reg[3];

	k = 0;
	while (k < 3)
	{
		place = take_arg_place(car, k);
		num_reg[i] = (unsigned char)take_arg_from_field(cw->field, place, 1);
		k += 1;
	}
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | sub r%d r%d r%d\n",
		car->num, num_reg[0], num_reg[1], num_reg[2]);*/
	temp = car->regs[num_reg[0]] - car->regs[num_reg[1]];
	car->regs[num_reg[2]] = temp;
	car->carry = (temp == 0) ? 1 : 0;
	replace_c(cw, car);
}
