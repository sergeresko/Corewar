/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:50:54 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/02 17:29:13 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			show_usage(t_vm const *vm)
{
	ft_printf("%susage: ./corewar [OPTIONS] [-dump[32|64] N] "
			"[[-n ID] NAME.cor] ...\n\n"
			"    -dump N, -dump32 N\n"
			"    -dump64 N\n"
			"        Dump the memory after N cycles and terminate "
			"(32 or 64 bytes per line).\n\n"
			"    -n ID\n"
			"        Set the id of the following champion to ID (1..4).\n\n"
			"    NAME.cor\n"
			"        File with a champion's bytecode "
			"(up to 4 champions in one battle).\n\n"
			"Options (in any order):\n"
			"    -h, -help           Show this message and quit.\n"
			"    -i, -interactive    Run in interactive mode.\n"
			"    -v, -verbose        Print detailed information during the "
			"battle.\n"
			"    -s, -silent         Do not report executions of \"live\".\n"
			"    -C, -canonic        Print same messages as the provided VM.\n"
			"    -c, -color          Enable colored output.\n"
			"    -l, -leaks          Check for leaks before terminating.\n%s",
			vm->opt.color ? PF_CYAN : "", vm->opt.color ? PF_RESET : "");
}
