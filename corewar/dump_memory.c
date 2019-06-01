/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:26 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 19:36:40 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		dump_memory_color(t_field const *field, int dump_bytes)
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
			ft_putstr(g_champ_colors[field[k].champ_id]);
			ft_printf("%02hhx ", field[k].square);
			++k;
		}
		ft_putstr("\n" PF_RESET);
	}
}

static void		dump_memory_plain(t_field const *field, int dump_bytes)
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

void			dump_memory(t_vm const *vm, int dump_bytes)
{
	if (vm->opt.color)
	{
		dump_memory_color(vm->field, dump_bytes);
	}
	else
	{
		dump_memory_plain(vm->field, dump_bytes);
	}
}
