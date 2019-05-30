/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_car.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:53:25 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/30 18:02:20 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			advance_car(t_vm const *vm, t_car *car)
{
	unsigned	place;
	unsigned	k;

	place = car->place;
	car->place = (car->place + car->offset) % MEM_SIZE;
	if (vm->verbose)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
				car->offset, place, car->place);
		k = car->offset;
		while (k--)
		{
			ft_printf("%02x ", read_from_field(vm->field, place, 1));
			place = (place + 1) % MEM_SIZE;
		}
		ft_putchar('\n');
	}
}
