/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:19 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 21:11:10 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_vm *vm, t_car *car)
{
	int const	value = get_arg_value(vm, car, 0);

	if (car->carry)
	{
		car->offset = value % IDX_MOD;
	}
	/*if (vm->ind->ops && !vm->ind->v)
	{
		ft_printf("P %4d | zjmp %d %s\n",
				car->num, value, car->carry ? "OK" : "FAILED");
	}*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
