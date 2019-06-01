/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:50:54 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 20:02:40 by syeresko         ###   ########.fr       */
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
			"Options:\n\n"
			"    -h, -help\n"
			"        Show this message and quit.\n\n"
			"    -v, -verbose\n"
			"        Print detailed information during the battle.\n\n"
			"    -s, -silent\n"
			"        Do not report executions of \"live\".\n\n"
			"    -i, -interactive\n"
			"        Run in interactive mode.\n\n"
			"    -c, -color\n"
			"        Enable colored output.\n\n"
			"    -l, -leaks\n"
			"        Check for leaks at the end of the battle.\n%s",
			vm->opt.color ? PF_CYAN : "", vm->opt.color ? PF_RESET : "");
}
