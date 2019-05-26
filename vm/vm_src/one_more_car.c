/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_more_car.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 16:26:41 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/26 16:26:42 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_regs(t_car *current)
{
	int k;

	k = 0;
	while (k < REG_NUMBER)
	{
		current->regs[k] = 0;
		k += 1;
	}
}

void		one_more_car(t_cw *data, t_champ *prev, int place)
{
	t_car *current;

	if (!(current = malloc(sizeof(t_car))))
		fail_sense(data, "Failed memmory allocation");
	data->carry_nbr++;
	data->alive_carry_nbr++;
	current->num = data->carry_nbr;
	current->place = place;
	current->carry = 0;
	current->opcode = 0;
	current->op_cycles_to_move = 0;
	current->prev = prev;
	current->args_nbr = 0;
	current->recent_cycle = 0;
	current->now_live = 0;
	current->then = NULL;
	init_regs(current);
	current->regs[1] = -prev->num;
	if (data->car)
		current->then = data->car;
	data->car = current;
}
