/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:36:14 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 19:07:46 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	write a sequence of four bytes representing `value` in big endian order
**	to `field` at position `place % MEM_SIZE`
*/

void			write_to_field(t_field *field,
								t_car const *car, int address, unsigned value)
{
	unsigned	place;
	int			size;

	place = car->place + address;
	size = 4;
	while (size--)
	{
		place %= MEM_SIZE;
		field[place].square = (unsigned char)(value >> (size << 3));
		field[place].champ_id = car->champ_id;
		++place;
	}
}
