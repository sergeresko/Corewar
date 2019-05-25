/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_arg_from_field.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:41:35 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 11:41:42 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	take_arg_from_field(t_field *field, unsigned int plc, int num)
{
	unsigned int	res;
	unsigned int	sup;

	res = 0;
	while (num > 0)
	{
		num -= 1;
		sup = (unsigned int)(field[plc % MEM_SIZE].square) << (num * 8);
		res |= sup;
		plc += 1;
	}
	return (res);
}
