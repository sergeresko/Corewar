/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_car.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:22:43 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/29 21:16:07 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car	*create_car(void)
{
	static int	id = 0;
	t_car		*car;

	if ((car = ft_memalloc(sizeof(t_car))) == NULL)	// initialized with zeroes
	{
		perror_exit("create_car");
	}
	++id;
	car->id = id;
	return (car);
}

