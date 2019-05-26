/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_amount_by_class.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:05:34 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 12:05:36 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern const t_ops g_ops[16];

int	take_amount_by_class(t_car *car, int k)
{
	if (car->arg_class[k] == T_DIR)
		return (S_TDIR(car->opcode));
	if (car->arg_class[k] == T_IND)
		return (IND_SIZE);
	if (car->arg_class[k] == T_REG)
		return (1);
	return (0);
}
