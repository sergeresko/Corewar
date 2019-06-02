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

/*
**	get the value stored in the register whose number is read from the field
*/

static int		get_value_reg(t_vm const *vm, t_car const *car, int place)
{
	int const	reg = read_from_field(vm->field, place, 1);

	return (car->regs[reg]);
}

/*
**	read the value from the field
*/

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

/*
**	get the value stored at the relative address read from the field
**
**	NOTE: The address is not trimmed by IDX_MOD for `lld`.
*/

static int		get_value_ind(t_vm const *vm, t_car const *car, int place)
{
	int			address;

	address = (short)read_from_field(vm->field, place, IND_SIZE);
	if (car->opcode != 13)
	{
		address %= IDX_MOD;
	}
	place = (car->place + address) % MEM_SIZE;
	return ((int)read_from_field(vm->field, place, 4));
}

/*
**	retrieve the value of the `arg`th argument according to is class
**
**	NOTE: Assuming our program is correct, the class will always be valid,
**	so this function will never terminate the program.
*/

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
	fatal_error("`car->arg_class` contains an incorrect value");
	return (0);
}
