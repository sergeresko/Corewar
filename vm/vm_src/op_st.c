/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:51:18 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/27 12:45:18 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_st(t_vm *vm, t_car *car)
{
	int const	reg = get_reg(vm, car, 0);
	int const	value = car->regs[reg];
	int			address;

	if (car->arg_class[1] == T_REG)
	{
		address = get_reg(vm, car, 1);
		car->regs[address] = value;
	}
	else
	{
		address = read_from_field(vm->field, car->arg_place[1], IND_SIZE);	// ?
		address %= IDX_MOD;
		write_to_field(vm->field, (car->place + address) % MEM_SIZE, value);
	}
	/*if (!vm->ind->v && vm->ind->ops)
		ft_printf("P %4d | st r%d %d\n",	// ??????????
		car->id, reg, address);*/
	car->place = (car->place + car->offset) % MEM_SIZE;
}
/*
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
		rewrite_field(cw, car, support, address);
	}
	//if (!cw->ind->v && cw->ind->ops)
	//	ft_printf("P %4d | st r%d %d\n",
	//	car->num, register_num, address);
	replace_c(cw, car);
}*/
