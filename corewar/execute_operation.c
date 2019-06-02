/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:20:11 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 16:10:48 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**		0            -> 0
**		1 (REG_CODE) -> 1 (T_REG)
**		2 (DIR_CODE) -> 2 (T_DIR)
**		3 (IND_CODE) -> 4 (T_IND)
** [	4            -> 8 (T_LAB)	]
*/

static int		arg_code_to_mask(int code)
{
	return (1 << code >> 1);
}

/*
**	read the coding byte from the field;
**	fill `arg_class`, `arg_place` and `offset` fields of `car` accordingly
*/

static int		decypher_coding_byte(t_vm const *vm, t_car *car)
{
	unsigned char	coding_byte;
	unsigned		offset;
	int				arg;
	int				is_valid;

	is_valid = TRUE;
	coding_byte = read_from_field(vm->field, car->place + 1, 1);
	offset = 2;
	arg = 0;
	while (arg < car->arg_amount)
	{
		car->arg_class[arg] = arg_code_to_mask(coding_byte >> 6);
		if (!(car->arg_class[arg] & g_ops[car->opcode].arg_list[arg]))
		{
			is_valid = FALSE;
		}
		car->arg_place[arg] = (car->place + offset) % MEM_SIZE;
		coding_byte <<= 2;
		offset += get_arg_size(car, arg);
		++arg;
	}
	car->offset = offset;
	return (is_valid);
}

/*
**	check whether a given number represents a number of a register
**	(return TRUE or FALSE)
*/

static int		is_valid_register(unsigned char number)
{
	return (1 <= number && number <= REG_NUMBER);
}

/*
**	check whether all register numbers are correct (return TRUE or FALSE)
*/

static int		check_registers(t_vm const *vm, t_car const *car)
{
	int				arg;
	unsigned char	reg;

	arg = 0;
	while (arg < car->arg_amount)
	{
		if (car->arg_class[arg] == T_REG)
		{
			reg = get_reg(vm, car, arg);
			if (!is_valid_register(reg))
			{
				return (FALSE);
			}
		}
		++arg;
	}
	return (TRUE);
}

/*
**	parse bytecode for an operation and either execute or skip it
**	depending on whether the coding byte and register numbers are valid
*/

void			execute_operation(t_vm *vm, t_car *car)
{
	car->arg_amount = g_ops[car->opcode].arg_amount;
	if (g_ops[car->opcode].has_coding_byte)
	{
		if (!decypher_coding_byte(vm, car) || !check_registers(vm, car))
		{
			advance_car(vm, car);
			return ;
		}
	}
	else
	{
		car->arg_class[0] = T_DIR;
		car->arg_place[0] = (car->place + 1) % MEM_SIZE;
		car->offset = 1 + get_arg_size(car, 0);
	}
	g_ops[car->opcode].operation(vm, car);
}
