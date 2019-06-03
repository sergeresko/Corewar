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

#define FMT		"ADV %d (0x%04x -> 0x%04x) "
#define FMT_COL	PF_CYAN FMT

#define END		"\n"
#define END_COL	END PF_RESET

void			advance_car(t_vm const *vm, t_car *car)
{
	unsigned	place;
	unsigned	k;

	place = car->place;
	car->place = (car->place + car->offset) % MEM_SIZE;
	if (vm->opt.verbose)
	{
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				car->offset, place, car->place);
		k = car->offset;
		while (k--)
		{
			ft_printf("%02x ", read_from_field(vm->field, place, 1));
			place = (place + 1) % MEM_SIZE;
		}
		ft_putstr(vm->opt.color ? END_COL : END);
	}
}
