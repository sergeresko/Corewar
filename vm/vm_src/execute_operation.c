/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:20:11 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/26 21:17:25 by syeresko         ###   ########.fr       */
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

static uint8_t	arg_code_to_mask(uint8_t code)
{
	return (1 << code >> 1);
}

/*
**	read the coding byte from the field;
**	fill `arg_class`, `arg_place` and `offset` fields of `car` accordingly
*/

void			decypher_coding_byte(t_vm const *vm, t_car *car)
{
	uint8_t		coding_byte;
	int			offset;		// unsigned short ?
	int			k;			// unsigned ?

	coding_byte = read_from_field(vm->field, (car->place + 1) % MEM_SIZE, 1);
	offset = 2;
	k = 0;
	while (k < car->arg_amount)
	{
		car->arg_class[k] = arg_code_to_mask(coding_byte >> 6);
		car->arg_place[k] = (car->place + offset) % MEM_SIZE;
		coding_byte <<= 2;
		offset += get_arg_size(car, k);
		++k;
	}
	car->offset = offset;
}

//--------------------------

/*
**	check whether a given number represents a number of a register
*/

static t_bool	is_valid_register(uint8_t number)
{
	return (1 <= number && number <= REG_NUMBER);
}

/*
**	check whether all register numbers are correct
*/

t_bool			check_registers(t_vm const *vm, t_car const *car)
{
	int			k;
	uint8_t		number;

	k = 0;
	while (k < car->arg_amount)
	{
		if (car->arg_class[k] == T_REG)
		{
			number = read_from_field(vm->field, car->arg_place[k], 1);
			if (!is_valid_register(number))
			{
				return (FALSE);
			}
		}
		++k;
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
		car->offset = 1 + get_arg_size(car, 0);
	}
	g_ops[car->opcode].operation(vm, car);
}
