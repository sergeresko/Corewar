/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 22:11:34 by syeresko         ###   ########.fr       */
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
	vm->last_living_champ_id = 0;
	vm->cars = NULL;
	vm->opt.help = FALSE;
	vm->opt.verbose = FALSE;
	vm->opt.silent = FALSE;
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
