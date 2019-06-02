/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:11:07 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/30 16:47:01 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	read `size` bytes from `field` at position `place % MEM_SIZE`
**	and construct an unsigned integer from them
**	assuming the bytes are in big endian order
*/

unsigned		read_from_field(t_field const *field, unsigned place, int size)
{
	unsigned	value;

	value = 0;
	while (size--)
	{
		place %= MEM_SIZE;
		value |= (unsigned)field[place].square << (size << 3);
		++place;
	}
	return (value);
}
