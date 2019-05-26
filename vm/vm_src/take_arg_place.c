/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_arg_place.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:44:42 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 11:44:44 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	take_arg_place(t_car *car, int indicator)
{
	int	place;
	int k;

	k = 0;
	place = car->place + 1;
	while (k < indicator)
	{
		place += take_amount_by_class(car, k);
		k += 1;
	}
	place %= MEM_SIZE;
	return (place);
}
