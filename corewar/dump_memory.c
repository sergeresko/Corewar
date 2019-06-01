/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:26 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 15:04:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO: colorize

void			dump_memory(t_field const *field, int dump_bytes)
{
	int			start;
	int			k;

	start = 0;
	k = 0;
	while (start < MEM_SIZE)
	{
		ft_printf("0x%04x : ", start);
		start += dump_bytes;
		while (k < start)
		{
			ft_printf("%02hhx ", field[k].square);
			++k;
		}
		ft_putchar('\n');
	}
}
