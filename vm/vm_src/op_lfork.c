/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:06:01 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 16:06:02 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_lfork(t_cw *cw, t_car *car)
{
	int				address;
	int				place;

	address = take_arg_by_class(cw, car, 0);
	place = car->place + (address);
	place %= MEM_SIZE;
	//создать новую каретку
	//скопировать в неё данные
	/*if (!cw->ind->v && cw->ind->ops)
		ft_printf("P %4d | lfork  %d (%d)\n",
		car->num, address, place);*/
	replace_c(cw, car);
}
