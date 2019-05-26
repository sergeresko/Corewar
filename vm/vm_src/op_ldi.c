/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:43 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 20:44:07 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_ldi(t_vm *vm, t_car *car)
{
	int const	operand_1 = get_arg_value(vm, car, 0);
	int const	operand_2 = get_arg_value(vm, car, 1);
	int const	place = (car->place + (operand_1 + operand_2) % IDX_MOD) % MEM_SIZE;	// line too long
	int const	value = get_arg_from_field(vm->field, place, 4);	// replace "4" with a define
	int const	reg = read_from_field(vm->field, car->arg_place[2], 1);

	car->regs[reg] = value;
	/*if (!vm->ind->v && vm->ind->ops)
	{
		ft_printf("P %4d | ldi %d %d r%d\n",
				car->num, operand_1, operand_2, reg);
	}*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
/*
void		op_ldi(t_cw *cw, t_car *car)
{
	int	amount1;
	int	amount2;
	int	place;
	int	num_reg;

	amount1 = take_arg_by_class(cw, car, 0);
	amount2 = take_arg_by_class(cw, car, 1);
	place = take_arg_place(car, 2);
	num_reg = (unsigned char)take_arg_from_field(cw->field, place, 1);
	place = car->place - 1 + ((amount1 + amount2) % IDX_MOD);
	car->regs[num_reg] = take_arg_from_field(cw->field, place, 4);
	//if (!cw->ind->v && cw->ind->ops)
	//{
	//	ft_printf("P %4d | ldi %d %d r%d\n",
	//	car->num, amount1, amount2, num_reg);
	//}
	replace_c(cw, car);
}*/
