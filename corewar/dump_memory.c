/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:26 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 17:02:51 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO: colorize

void			dump_memory(t_vm const *vm)
{
	int			start;
	int			k;

	start = 0;
	k = 0;
	while (start < MEM_SIZE)
	{
		ft_printf("0x%04x : ", start);
		start += vm->dump_bytes;
		while (k < start)
		{
			ft_printf("%02hhx ", vm->field[k].square);
			++k;
		}
		ft_putchar('\n');
	}
}
