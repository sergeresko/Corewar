/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_arg_by_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:58:19 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 15:58:20 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern const t_ops g_ops[16];

static int	take_arg_class_reg(t_field *field, t_car *car, int place)
{
	unsigned char	num_reg;

	num_reg = (unsigned char)take_arg_from_field(field, place, 1);
	return (car->regs[num_reg]);
}

static int	take_arg_class_dir(t_field *field, t_car *car, int place)
{
	int	result;
	int	amount;

	amount = S_TDIR(car->opcode);
	if (amount == 2)
		result = (short)take_arg_from_field(field, place, 2);
	else
		result = (int)take_arg_from_field(field, place, 4);
	return (result);
}

static int	take_arg_class_ind(t_field *field, t_car *car, int place)
{
	int	result;
	int	address;

	address = (short)take_arg_from_field(field, place, IND_SIZE);
	if (car->opcode != 13)
		address %= IDX_MOD;
	result = (int)take_arg_from_field(field, car->place + address - 1, 4);
	return (result);
}

int			take_arg_by_class(t_cw *cw, t_car *car, int indicator)
{
	int	class;
	int place;

	class = car->arg_class[indicator];
	place = take_arg_place(car, indicator);
	if (class == T_REG)
		return (take_arg_class_reg(cw->field, car, place));
	if (class == T_DIR)
		return (take_arg_class_dir(cw->field, car, place));
	else
		return (take_arg_class_ind(cw->field, car, place));
}
