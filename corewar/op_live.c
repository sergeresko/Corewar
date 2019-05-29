/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:50:57 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:51:00 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	live_champ(t_vm *vm, int k, int place)
{
	(void)vm;
	(void)k;
	(void)place;
/* TODO:
	//if (cw->ind->v)
	//{
	//	smth
	//}
	cw->last_champ = &cw->champ[k];
	cw->champ[k].ongoing_lives++;
	cw->champ[k].recent_cycle = cw->ongoing_cycle;
	//if (cw->ind->lives && !cw->ind->v)
	//	ft_printf("Player %d (%s) is said to be alive\n",
	//	cw->champ[k].num, cw->champ[k].name);
*/
}

void		op_live(t_vm *vm, t_car *car)
{
	(void)vm;
	(void)car;
	(void)live_champ;
/* TODO:
	int	parameter;
	int	k;
	int	amount;

	car->now_live = 1;
	cw->alive_nbr++;
	car->recent_cycle = cw->ongoing_cycle;
	amount = S_TDIR(car->opcode);
	parameter = (int)take_arg_from_field(cw->field, car->place + 1, amount);
	k = 0;
	//if (cw->ind->ops && !cw->ind->v)
	//	ft_printf("P %4d | live %d\n", car->id, parameter);
	while (k < cw->champs_amount)
	{
		if (parameter == -cw->champ[k].num)
		{
			live_champ(cw, k, car->place);
			break ;
		}
		k += 1;
	}
	replace_c(cw, car);
*/
}
