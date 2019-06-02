/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/02 17:47:20 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	initialize the first four fields of the virtual machine structure
**	(champions and processes) as well as all options (the last four fields)
**
**	NOTE: `dump_bytes` might be left uninitialized.
*/

static void		init_vm(t_vm *vm)
{
	vm->champ_amount = 0;
	vm->champs = NULL;
	vm->cars = NULL;
	vm->opt.help = FALSE;
	vm->opt.verbose = FALSE;
	vm->opt.silent = FALSE;
	vm->opt.canonic = FALSE;
	vm->opt.color = FALSE;
	vm->opt.leaks = FALSE;
	vm->interactive_cycle = -1;
	vm->dump_cycle = -1;
	vm->dump_bytes = 32;
}

static void		get_options(t_vm *vm, char **av)
{
	av = get_opt_bonus(vm, av);
	av = get_opt_dump(vm, av);
	get_opt_champs(vm, av);
	set_champ_ids(vm->champs, vm->champ_amount);
	read_champs(vm->champs);
}

int				main(int ac, char **av)
{
	t_vm		vm;

	init_vm(&vm);
	get_options(&vm, av);
	if (ac < 2 || vm.opt.help)
	{
		show_usage(&vm);
	}
	else if (vm.champ_amount == 0)
	{
		fatal_error("No champions");
	}
	else
	{
		perform_battle(&vm);
	}
	if (vm.opt.leaks)
	{
		system(LEAKS_COMMAND);
	}
	return (0);
}

/*
**	If you want to automatically compare the output of this virtual machine and
**	the machine provided in the task (for example with `diff`), their output
**	must be in the same format.
**
**	(1)	Running the original VM without options should be equivalent to running
**		our VM with `-silent` and `-canonic` options:
**
**		original VM:	`./corewar ...`
**		our VM:			`./corewar -s -C ...`
**
**	(2)	Our VM should print the same information in the verbose mode as the
**		original one with full detalization and output from `aff` enabled:
**
**		original VM:	`./corewar -v 31 -a ...`
**		our VM:			`./corewar -v -C ...`
**
**	(3)	The original machine's `-d` flag is equivalent to our `-dump64`:
**
**		original VM:	`./corewar ... -d ...`
**		our VM:			`./corewar ... -dump64 ...`
*/
