/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:36:08 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/27 12:59:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include

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
	ft_printf("`car->arg_class` contains an incorrect value\n");	//
	exit(-1);														//
	return (0);					// this should never happen
}
