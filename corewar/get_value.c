/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:36:08 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 12:38:59 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_value_reg(t_vm const *vm, t_car const *car, int place)
{
	int const	reg = read_from_field(vm->field, place, 1);

	return (car->regs[reg]);
}

static int		get_value_dir(t_vm const *vm, t_car const *car, int place)
{
	int const	size = g_ops[car->opcode].dir_size;

	if (size == 2)
	{
		return ((short)read_from_field(vm->field, place, size));
	}
	else
	{
		return ((int)read_from_field(vm->field, place, size));
	}
}

static int		get_value_ind(t_vm const *vm, t_car const *car, int place)
{
	int			address;

	address = (short)read_from_field(vm->field, place, IND_SIZE);
	if (car->opcode != 13)		// not `lld`
	{
		address %= IDX_MOD;
	}
	place = (car->place + address) % MEM_SIZE;
	return ((int)read_from_field(vm->field, place, 4));
}

void		_diagnostic_error_message(t_vm const *vm, t_car const *car, int arg)////////////////
{
	(void)vm;
	(void)arg;
	ft_printf("car (id: %d):\n", car->id);
	ft_printf("  place: 0x%04x\n", car->place);
	ft_printf("  opcode: %d\n", car->opcode);
	ft_printf("  arg_amount: %d\n", car->arg_amount);
	ft_printf("  arg_class[]: %d, %d, %d\n", car->arg_class[0], car->arg_class[1], car->arg_class[2]);
	ft_printf("  arg_place[]: 0x%04x, 0x%04x, 0x%04x\n", car->arg_place[0], car->arg_place[1], car->arg_place[2]);
}

int				get_value(t_vm const *vm, t_car const *car, int arg)
{
	int const	class = car->arg_class[arg];
	int const	place = car->arg_place[arg];

	if (class == T_REG)
	{
		return (get_value_reg(vm, car, place));
	}
	if (class == T_DIR)
	{
		return (get_value_dir(vm, car, place));
	}
	if (class == T_IND)
	{
		return (get_value_ind(vm, car, place));
	}
	_diagnostic_error_message(vm, car, arg);//////////////////////
	fatal_error("`car->arg_class` contains an incorrect value");	//
	return (0);					// this should never happen
}
