/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:36:08 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/26 17:15:01 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include

static int	get_reg_value(t_vm const *vm, t_car const *car, uint16_t place)
{
	uint8_t const	reg_index = take_arg_from_field(vm->field, place, 1);

	return (car->registers[reg_index]);
}

static int	get_dir_value(t_vm const *vm, t_car const *car, uint16_t place)
{
	uint8_t const	size = g_ops[car->opcode].dir_size;

	return (take_arg_from_field(vm->field, place, size));
}

static int	get_ind_value(t_vm const *vm, t_car const *car, uint16_t place)
{
	// TODO:
}

int			get_arg_value(t_vm const *vm, t_car const *car, int k)
{
	uint8_t const	class = car->arg_class[k];
	uint16_t const	place = car->arg_place[k];

	if (class == T_REG)
	{
		return (get_reg_value(vm, car, place));
	}
	if (class == T_DIR)
	{
		return (get_dir_value(vm, car, place));
	}
	if (class == T_IND)
	{
		return (get_ind_value(vm, car, place));
	}
	ft_printf("`car->arg_class` contains an incorrect value\n");	//
	exit(-1);														//
	return (0);					// this should never happen
}
