/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:50 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:52:51 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_aff(t_cw *cw, t_car *car)
{
	int	register_num;
	int	place;
	int	amount;

	place = car->place + 1;
	register_num = (unsigned char)take_arg_from_field(cw->field, place, 1);
	amount = car->regs[register_num];
	/*if (!cw->ind->v)
		ft_printf("Aff: %c\n", (char)amount);*/
	replace_c(cw, car);
}
