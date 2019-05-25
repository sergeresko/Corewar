/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:58:09 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:58:10 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	rewrite_field(t_cw *cw, t_car *car, int amount, int address)
{
	int	place;
	int	amount;
	int	temp;

	place = (car->place - 1 + address) % MEM_SIZE;
	amount = 4;
	while (amount)
	{
		amount -= 1;
		temp = amount >> (amount * 8);
		cw->field[place % MEM_SIZE].square = (unsigned char)temp;
		cw->field[place % MEM_SIZE].cycles = 50;
		place += 1;
	}
}
