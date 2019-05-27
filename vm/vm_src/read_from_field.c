/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:11:07 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/27 12:54:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned	read_from_field(t_field const *field, int place, int size)
{
	unsigned 	value;

	value = 0;
	while (size--)
	{
		place %= MEM_SIZE;
		value |= (unsigned)field[place].square << (size * 8);
		++place;
	}
	return (value);
}
