/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_car.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:52:07 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/02 13:05:50 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	`place` is automatically taken modulo `MEM_SIZE`
*/

t_car			*clone_car(t_car const *car, unsigned place)
{
	t_car		*new_car;
	int			id;

	new_car = create_car();
	id = new_car->id;
	ft_memcpy(new_car, car, sizeof(t_car));
	new_car->id = id;
	new_car->place = place % MEM_SIZE;
	return (new_car);
}
