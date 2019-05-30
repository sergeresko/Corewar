/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:36:14 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/30 16:49:11 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	write a sequence of four bytes representing `value` in big endian order
**	to `field` at position `place` % MEM_SIZE
*/

void		write_to_field(t_field *field, unsigned place, unsigned value)
{
	int		size;

	size = 4;
	while (size--)
	{
		place %= MEM_SIZE;
		field[place].square = (uint8_t)(value >> (size * 8));
		//field[place].cycles = 50;
		++place;
	}
}
