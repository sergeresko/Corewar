/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:52:19 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:52:20 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern const t_ops g_ops[16];

void	op_zjmp(t_cw *cw, t_car *car)
{
	unsigned int	plc;
	short			moveln;
	short			tmp;
	char			*carry;

	plc = car->place;
	tmp = S_TDIR(car->opcode);
	/*if (cw->ind->ops && !cw->ind->v)
	{
		carry = (car->carry) ? "OK" : "FAILED";
		moveln = (short)take_arg_from_field(cw->field, plc + 1, tmp);
		ft_printf("P %4d | zjmp %d %s\n", car->num, moveln, carry);
	}*/
	if (car->carry)
	{
		moveln = (short)take_arg_from_field(cw->field, plc + 1, tmp) % IDX_MOD;
		car->place = (plc + moveln) % MEM_SIZE;
	}
	else
		replace_c(cw, car);
}
