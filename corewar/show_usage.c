/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:50:54 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 13:03:29 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		show_usage(t_vm const *vm)
{
	if (vm->color)
		ft_putstr(PF_CYAN);
	ft_putstr("usage: ./corewar [-h -v -c -l] "
			"[-dump[32|64] NBR_CYCLES] [[-n ID] NAME.cor] ...\n\n"
			"    -h, -help\n"
			"        Show this message.\n\n"
			"    -v, -verbose\n"
			"        Print detailed information during execution.\n\n"
			"    -c, -color\n"
			"        Enable colored output.\n\n"
			"    -l, -leaks\n"
			"        Check for leaks at the end of execution.\n\n"
			"    -dump NBR_CYCLES, -dump32 NBR_CYCLES\n"
			"    -dump64 NBR_CYCLES\n"
			"        Dump the memory after NBR_CYCLES and quit the game\n"
			"        (32 or 64 bytes per line).\n\n"
			"    -n ID\n"
			"        Set the id of the following champion to ID (1..4).\n\n"
			"    NAME.cor\n"
			"        File with a champion's bytecode "
			"(up to 4 champions in one battle).\n");
	if (vm->color)
		ft_putstr(PF_RESET);
}
