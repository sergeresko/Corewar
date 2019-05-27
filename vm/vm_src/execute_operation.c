/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:20:11 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/27 13:58:40 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include

/*
**		0            -> 0
**		1 (REG_CODE) -> 1 (T_REG)
**		2 (DIR_CODE) -> 2 (T_DIR)
**		3 (IND_CODE) -> 4 (T_IND)
** [	4            -> 8 (T_LAB)	]
*/

static int	arg_code_to_mask(int code)
{
	return (1 << code >> 1);
}

/*
**	read the coding byte from the field;
**	fill `arg_class`, `arg_place` and `offset` fields of `car` accordingly
*/

void			decypher_coding_byte(t_vm const *vm, t_car *car)
{
	uint8_t		coding_byte;	// TODO: rewrite so that `coding_byte` can be `int`
	int			offset;
	int			arg;

	coding_byte = read_from_field(vm->field, (car->place + 1) % MEM_SIZE, 1);
	offset = 2;
	arg = 0;
	while (arg < car->arg_amount)
	{
		car->arg_class[arg] = arg_code_to_mask(coding_byte >> 6);
		car->arg_place[arg] = (car->place + offset) % MEM_SIZE;
		coding_byte <<= 2;
		offset += get_arg_size(car, arg);	// <-- `get_arg_size`
		++arg;
	}
	car->offset = offset;
}

//--------------------------

/*
**	check whether a given number represents a number of a register
**	(return TRUE or FALSE)
*/

static int	is_valid_register(uint8_t number)
{
	return (1 <= number && number <= REG_NUMBER);
}

/*
**	check whether all register numbers are correct (return TRUE or FALSE)
*/

int			check_registers(t_vm const *vm, t_car const *car)
{
	int			arg;
	uint8_t		reg;

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

//--------------------------

void	execute_operation(t_vm *vm, t_car *car)
{
	car->arg_amount = g_ops[car->opcode].arg_amount;
	if (g_ops[car->opcode].has_coding_byte)
	{
		decypher_coding_byte(vm, car);
		if (!check_registers(vm, car))
		{
			car->place = (car->place + car->offset) % MEM_SIZE;
			return ;
		}
	}
	else
	{
		car->arg_class[0] = T_DIR;
		car->arg_place[0] = (car->place + 1) % MEM_SIZE;
		car->offset = 1 + get_arg_size(car, 0);		// <-- `get_arg_size`
	}
	g_ops[car->opcode].operation(vm, car);
}
